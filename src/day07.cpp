#include "inputs/day07.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;
using std::operator""sv;

constexpr int numberOfCards = 5;

struct Hand
{
	std::string cards;
	int64_t bid{};
};

using Hands = std::vector<Hand>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	Hands hands;
	Hand tempHand;
};

struct CardsRule : pegtl::rep<numberOfCards, pegtl::alnum>
{};

struct BidRule : pegtl::plus<pegtl::digit>
{};

struct LineRule : pegtl::seq<CardsRule, pegtl::blank, BidRule, pegtl::eolf>
{};

struct Grammar : pegtl::must<pegtl::until<pegtl::eof, LineRule>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<CardsRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempHand.cards = in.string();
	}
};

template<>
struct Action<BidRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempHand.bid = std::stoll(in.string());
	}
};

template<>
struct Action<LineRule>
{
	static void apply0(State& state)
	{
		state.hands.push_back(state.tempHand);
	}
};

Hands parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return state.hands;
}

} // namespace Parsing

enum class HandType
{
	highCard,
	OnePair,
	TwoPair,
	Three,
	Full,
	Four,
	Five,
};

std::vector<int64_t> getCounter(const std::string& cards)
{
	std::vector<int64_t> result(2);
	const auto counter = cards | vw::filter([](char c) { return c != 'J'; })
		| vw::transform([&](char c) { return std::pair{c, rng::count(cards, c)}; })
		| rng::to<std::map>() | vw::values;
	rng::partial_sort_copy(counter, result, rng::greater{});
	return result;
}

HandType getHandType(const std::string& cards)
{
	const auto jokers = rng::count(cards, 'J');
	const auto counter = getCounter(cards);
	const auto first = counter.at(0) + jokers;
	const auto second = counter.at(1);

	if (first == 5)
		return HandType::Five;
	else if (first == 4)
		return HandType::Four;
	else if (first == 3)
		return second == 2 ? HandType::Full : HandType::Three;
	else if (first == 2)
		return second == 2 ? HandType::TwoPair : HandType::OnePair;

	return HandType::highCard;
}

std::vector<int> getCardValues(const std::string& cards)
{
	constexpr auto orderedCards = "J23456789TXQKA"sv;
	return cards | vw::transform([&](char c) { return static_cast<int>(orderedCards.find(c)); })
		| rng::to<std::vector>();
}

int64_t getOverallRating(Hands hands)
{
	rng::sort(hands, [](const Hand& lhs, const Hand& rhs) {
		const HandType leftType = getHandType(lhs.cards);
		const HandType rightType = getHandType(rhs.cards);
		if (leftType != rightType)
			return leftType < rightType;

		return getCardValues(lhs.cards) < getCardValues(rhs.cards);
	});

	return Utils::sum(hands | vw::enumerate | vw::transform([](const auto& p) {
		const auto& [index, hand] = p;
		return (index + 1) * hand.bid;
	}));
}

int64_t solvePart1(std::string_view input)
{
	const Hands hands = Parsing::parse(input) | vw::transform([](Hand& hand) {
		rng::replace(hand.cards, 'J', 'X');
		return hand;
	}) | rng::to<std::vector>();

	return getOverallRating(hands);
}

int64_t solvePart2(std::string_view input)
{
	return getOverallRating(Parsing::parse(input));
}

TEST(day07, test)
{
	EXPECT_EQ(solvePart1(day07::sample), 6440);
	EXPECT_EQ(solvePart1(day07::input), 248179786);

	EXPECT_EQ(solvePart2(day07::sample), 5905);
	EXPECT_EQ(solvePart2(day07::input), 247885995);
}

} // anonymous namespace
