#include "inputs/day04.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <set>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

using Numbers = std::vector<int64_t>;

struct Card
{
	int64_t id{};
	Numbers winningNumbers;
	Numbers numbers;
};

using Cards = std::vector<Card>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	Cards cards;
	Card tempCard;
};

struct Digits : pegtl::plus<pegtl::digit>
{};

struct CardNumber : Digits
{};

struct WinningNumber : Digits
{};

struct Number : Digits
{};

struct Separator : pegtl::plus<pegtl::blank>
{};

struct Line
	: public pegtl::seq<
		  TAO_PEGTL_STRING("Card"),
		  Separator,
		  CardNumber,
		  pegtl::one<':'>,
		  Separator,
		  pegtl::list<WinningNumber, Separator>,
		  Separator,
		  pegtl::one<'|'>,
		  Separator,
		  pegtl::list<Number, Separator>,
		  pegtl::eolf>
{};

struct File : pegtl::must<pegtl::until<pegtl::eof, Line>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<CardNumber>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCard.id = std::stoi(in.string());
	}
};

template<>
struct Action<WinningNumber>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCard.winningNumbers.push_back(std::stoi(in.string()));
	}
};

template<>
struct Action<Number>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCard.numbers.push_back(std::stoi(in.string()));
	}
};

template<>
struct Action<Line>
{
	static void apply0(State& state)
	{
		state.cards.push_back(state.tempCard);
		state.tempCard = {};
	}
};

Cards parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<File, Action>(in, state);
	return state.cards;
}

} // namespace Parsing

template<rng::range RangeT>
auto getIntersectionSize(
	RangeT&& lhs, RangeT&& rhs) // NOLINT(cppcoreguidelines-missing-std-forward)
{
	const auto s1 = lhs | rng::to<std::set>();
	const auto s2 = rhs | rng::to<std::set>();
	std::vector<rng::range_value_t<RangeT>> intersection;
	rng::set_intersection(lhs, rhs, std::back_inserter(intersection));
	return std::ranges::ssize(intersection);
}

int64_t solvePart1(std::string_view input)
{
	const Cards cards = Parsing::parse(input);
	return Utils::sum(cards | vw::transform([](const Card& card) {
						  return (1 << getIntersectionSize(card.winningNumbers, card.numbers)) >> 1;
					  }));
}

int64_t solvePart2(std::string_view input)
{
	const Cards cards = Parsing::parse(input);
	std::vector<int> cardsCount(cards.size(), 1);
	for (const Card& card : cards)
	{
		const int64_t intersectionSize = getIntersectionSize(card.winningNumbers, card.numbers);
		for (const auto i : vw::iota(card.id, std::min(card.id + intersectionSize, ssize(cards))))
			cardsCount.at(i) += cardsCount.at(card.id - 1);
	}

	return Utils::sum(cardsCount);
}

TEST(day04, test)
{
	EXPECT_EQ(solvePart1(day04::sample), 13);
	EXPECT_EQ(solvePart1(day04::input), 21485);

	EXPECT_EQ(solvePart2(day04::sample), 30);
	EXPECT_EQ(solvePart2(day04::input), 11024379);
}

} // anonymous namespace
