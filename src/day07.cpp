#include "inputs/day07.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <ranges>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;
using std::operator""sv;

struct Hand
{
	std::string cards;
	int64_t bid;
};

using Hands = std::vector<Hand>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	Hands hands;
	Hand currentHand;
};

struct CardsRule : pegtl::rep<5, pegtl::alnum>
{
};

struct BidRule : pegtl::plus<pegtl::digit>
{
};

struct LineRule : pegtl::seq<CardsRule, pegtl::blank, BidRule, pegtl::eolf>
{
};

struct Grammar : pegtl::must<pegtl::until<pegtl::eof, LineRule>>
{
};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{
};

template<>
struct Action<CardsRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.currentHand.cards = in.string();
	}
};

template<>
struct Action<BidRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.currentHand.bid = (std::stoll(in.string()));
	}
};

template<>
struct Action<LineRule>
{
	static void apply0(State& state)
	{
		state.hands.push_back(state.currentHand);
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

HandType getHandType(const Hand& hand)
{
	const auto jokers = std::ranges::count(hand.cards, 'J');
	auto count = hand.cards | vw::filter([](char c) { return c != 'J'; })
		| vw::transform(
					 [&](char c) { return std::make_pair(c, std::ranges::count(hand.cards, c)); })
		| std::ranges::to<std::map>() | vw::values | std::ranges::to<std::vector>();
	std::ranges::sort(count, std::ranges::greater{});

	if (count.empty())
		return HandType::Five;

	count.at(0) += jokers;

	if (count.at(0) == 5)
		return HandType::Five;
	else if (count.at(0) == 4)
		return HandType::Four;
	else if (count.at(0) == 3)
		return count.at(1) == 2 ? HandType::Full : HandType::Three;
	else if (count.at(0) == 2)
		return count.at(1) == 2 ? HandType::TwoPair : HandType::OnePair;

	return HandType::highCard;
}

std::vector<int> getCardValues(const std::string& cards)
{
	constexpr auto orderedCards = "J23456789TXQKA"sv;
	return cards | vw::transform([=](char c) { return static_cast<int>(orderedCards.find(c)); })
		| std::ranges::to<std::vector>();
}

int64_t getOverallRating(Hands hands)
{
	std::ranges::sort(hands, [](const Hand& lhs, const Hand& rhs) {
		const HandType leftType = getHandType(lhs);
		const HandType rightType = getHandType(rhs);
		if (leftType != rightType)
			return leftType < rightType;

		return getCardValues(lhs.cards) < getCardValues(rhs.cards);
	});

	return std::ranges::fold_left(
		hands | vw::enumerate | vw::transform([](const auto& p) {
			const auto& [index, hand] = p;
			return (index + 1) * hand.bid;
		}),
		0,
		std::plus{});
}

int64_t solvePart1(std::string_view input)
{
	auto hands = Parsing::parse(input) | vw::transform([](Hand& hand) {
					 std::ranges::replace(hand.cards, 'J', 'X');
					 return hand;
				 })
		| std::ranges::to<std::vector>();

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
