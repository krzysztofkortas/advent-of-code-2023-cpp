#include "inputs/day20.h"

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;
using std::operator""s;

namespace Parsing
{

namespace pegtl = tao::pegtl;

enum class ModuleType
{
	flipFlop,
	conjunction,
	broadcast
};

struct Module
{
	ModuleType type{};
	std::string name;
	std::vector<std::string> outputs;
};

using Modules = std::vector<Module>;

struct State
{
	Modules modules;
	Module tempModule;
};

struct ModuleNameRule : pegtl::plus<pegtl::alpha>
{};

struct FlipFlopModuleRule : pegtl::seq<pegtl::one<'%'>, ModuleNameRule>
{};

struct ConjunctionModuleRule : pegtl::seq<pegtl::one<'&'>, ModuleNameRule>
{};

struct BroadcastModuleRule : ModuleNameRule
{};

struct OutputModuleRule : ModuleNameRule
{};

struct LineRule
	: pegtl::seq<
		  pegtl::sor<FlipFlopModuleRule, ConjunctionModuleRule, BroadcastModuleRule>,
		  TAO_PEGTL_STRING(" -> "),
		  pegtl::list<OutputModuleRule, pegtl::one<','>, pegtl::blank>,
		  pegtl::eolf>
{};

struct Grammar : pegtl::must<pegtl::until<pegtl::eof, LineRule>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<ModuleNameRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempModule.name = in.string();
	}
};

template<>
struct Action<FlipFlopModuleRule>
{
	static void apply0(State& state)
	{
		state.tempModule.type = ModuleType::flipFlop;
	}
};

template<>
struct Action<ConjunctionModuleRule>
{
	static void apply0(State& state)
	{
		state.tempModule.type = ModuleType::conjunction;
	}
};

template<>
struct Action<BroadcastModuleRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempModule.type = ModuleType::broadcast;
		state.tempModule.name = in.string();
	}
};

template<>
struct Action<OutputModuleRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempModule.outputs.push_back(in.string());
	}
};

template<>
struct Action<LineRule>
{
	static void apply0(State& state)
	{
		state.modules.push_back(state.tempModule);
		state.tempModule = {};
	}
};

Modules parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return state.modules;
}

} // namespace Parsing

auto associateWith(rng::range auto&& range, const auto& value)
{
	return range | vw::transform([&](const auto& key) { return std::pair{key, value}; })
		| rng::to<std::map>();
}

class FlipFlopModule
{
public:
	explicit FlipFlopModule(std::vector<std::string> outputs)
		: outputs_{std::move(outputs)}
	{
	}

	[[nodiscard]] std::map<std::string, bool> send(bool pulse, const std::string&)
	{
		if (pulse)
			return {};
		enabled_ = !enabled_;
		return associateWith(outputs_, enabled_);
	}

	[[nodiscard]] std::vector<std::string> getOutputs() const
	{
		return outputs_;
	}

private:
	std::vector<std::string> outputs_;
	bool enabled_ = false;
};

class ConjunctionModule
{
public:
	explicit ConjunctionModule(std::vector<std::string> outputs, rng::range auto&& inputs)
		: outputs_{std::move(outputs)}
		, lastPulses_{associateWith(inputs, false)}
	{
	}

	[[nodiscard]] std::map<std::string, bool> send(bool pulse, const std::string& input)
	{
		lastPulses_[input] = pulse;
		return associateWith(
			outputs_, rng::any_of(lastPulses_ | vw::values, [](bool p) { return !p; }));
	}

	[[nodiscard]] std::vector<std::string> getOutputs() const
	{
		return outputs_;
	}

private:
	std::vector<std::string> outputs_;
	std::map<std::string, bool> lastPulses_;
};

class BroadcastModule
{
public:
	explicit BroadcastModule(std::vector<std::string> outputs)
		: outputs_{std::move(outputs)}
	{
	}

	[[nodiscard]] std::map<std::string, bool> send(bool pulse, const std::string&) const
	{
		return associateWith(outputs_, pulse);
	}

	[[nodiscard]] std::vector<std::string> getOutputs() const
	{
		return outputs_;
	}

private:
	std::vector<std::string> outputs_;
};

using Module = std::variant<FlipFlopModule, ConjunctionModule, BroadcastModule>;
using ModulesMap = std::map<std::string, Module>;

ModulesMap getModules(std::string_view input)
{
	const Parsing::Modules modules = Parsing::parse(input);
	const auto getInputs = [&](const std::string& moduleName) {
		return modules | vw::filter([&](const Parsing::Module& module) {
			return rng::count(module.outputs, moduleName) > 0;
		}) | vw::transform(&Parsing::Module::name);
	};
	return modules | vw::transform([&](const Parsing::Module& parsedModule) {
		const auto module = [&]() -> Module {
			switch (parsedModule.type)
			{
				case Parsing::ModuleType::flipFlop:
					return FlipFlopModule{parsedModule.outputs};
				case Parsing::ModuleType::conjunction:
					return ConjunctionModule{parsedModule.outputs, getInputs(parsedModule.name)};
				case Parsing::ModuleType::broadcast:
					return BroadcastModule{parsedModule.outputs};
			}
			std::unreachable();
		}();
		return std::pair{parsedModule.name, module};
	}) | rng::to<ModulesMap>();
}

void pushButton(ModulesMap& modules, std::invocable<std::string, bool, std::string> auto onPulse)
{
	std::tuple init{"broadcaster"s, false, ""s};

	for (std::queue<std::tuple<std::string, bool, std::string>> q{{init}}; !q.empty(); q.pop())
	{
		const auto& [destination, pulse, from] = q.front();
		onPulse(destination, pulse, from);

		if (const auto it = modules.find(destination); it != modules.cend())
		{
			const auto sendVisitor = [&](auto& module) {
				return module.send(pulse, from); // NOLINT
			};
			for (const auto& [key, value] : std::visit(sendVisitor, it->second))
				q.emplace(key, value, destination);
		}
	}
}

int64_t getPulsesMultiply(ModulesMap& modules, int64_t times)
{
	std::map<bool, int64_t> pulseCount;

	rng::for_each(vw::iota(0, times), [&](int) {
		pushButton(modules, [&](const std::string&, bool pulse, const std::string&) {
			++pulseCount[pulse];
		});
	});

	return pulseCount[false] * pulseCount[true];
}

int64_t solvePart1(std::string_view input)
{
	ModulesMap modules = getModules(input);
	constexpr int times = 1000;
	return getPulsesMultiply(modules, times);
}

auto getInputs(const ModulesMap& modules, const std::string& moduleName)
{
	const auto getInputsVisitor = [&moduleName](const auto& module) {
		return rng::count(module.getOutputs(), moduleName) > 0;
	};
	return modules | vw::filter([getInputsVisitor](const auto& p) {
		const auto& [_, module] = p;
		return std::visit(getInputsVisitor, module);
	}) | vw::keys;
}

int64_t pushesToGetRx(ModulesMap& modules)
{
	const auto beforeRxName = getInputs(modules, "rx").front();
	auto beforeRxInputsCounts = getInputs(modules, beforeRxName)
		| vw::transform([](const std::string& moduleName) { return std::pair{moduleName, 0LL}; })
		| rng::to<std::map>();

	const auto anyZero = [&]() {
		return rng::any_of(beforeRxInputsCounts | vw::values, [](int64_t val) { return val == 0; });
	};
	for (int64_t pushCount = 1; anyZero(); ++pushCount)
	{
		pushButton(
			modules, [&](const std::string& destination, bool pulse, const std::string& from) {
			if (destination == beforeRxName && pulse)
				beforeRxInputsCounts[from] = pushCount;
		});
	}

	return rng::fold_left_first(beforeRxInputsCounts | vw::values, [](int64_t x, int64_t y) {
		return std::lcm(x, y);
	}).value_or(0);
}

int64_t solvePart2(std::string_view input)
{
	ModulesMap modules = getModules(input);
	return pushesToGetRx(modules);
}

TEST(day20, test)
{
	EXPECT_EQ(solvePart1(day20::sample1), 32000000);
	EXPECT_EQ(solvePart1(day20::sample2), 11687500);
	EXPECT_EQ(solvePart1(day20::input), 825896364);

	EXPECT_EQ(solvePart2(day20::input), 243566897206981);
}

} // anonymous namespace
