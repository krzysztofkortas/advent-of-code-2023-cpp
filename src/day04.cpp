#include "inputs/day04.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <ranges>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

using Numbers = std::vector<int>;

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

struct Digits : pegtl::plus<pegtl::digit>
{
};

struct CardNumber : Digits
{
};

struct WinningNumber : Digits
{
};

struct Number : Digits
{
};

struct Separator : pegtl::plus<pegtl::blank>
{
};

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
{
};

struct File : pegtl::must<pegtl::until<pegtl::eof, Line>>
{
};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{
};

template<>
struct Action<CardNumber>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Cards& cards)
	{
		assert(!cards.empty());
		cards.back().id = std::stoi(in.string());
	}
};

template<>
struct Action<WinningNumber>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Cards& cards)
	{
		assert(!cards.empty());
		cards.back().winningNumbers.push_back(std::stoi(in.string()));
	}
};

template<>
struct Action<Number>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Cards& cards)
	{
		assert(!cards.empty());
		cards.back().numbers.push_back(std::stoi(in.string()));
	}
};

template<typename Rule>
struct Control : pegtl::normal<Rule>
{
};

template<>
struct Control<Line> : pegtl::normal<Line>
{
	template<typename ParseInput>
	static void start(ParseInput&, Cards& cards)
	{
		cards.emplace_back();
	}
};

Cards parse(std::string_view input)
{
	Cards cards;
	pegtl::memory_input in{input, ""};
	pegtl::parse<File, Action, Control>(in, cards);
	return cards;
}

} // namespace Parsing

template<typename ContainerT>
	requires std::ranges::range<ContainerT>
auto getIntersectionSize(ContainerT lhs, ContainerT rhs)
{
	std::ranges::sort(lhs);
	std::ranges::sort(rhs);
	ContainerT intersection;
	std::ranges::set_intersection(lhs, rhs, std::back_inserter(intersection));
	return std::ssize(intersection);
}

int64_t solvePart1(std::string_view input)
{
	const auto cards = Parsing::parse(input);
	return std::ranges::fold_left(
		cards | vw::transform([](const Card& card) {
			const int intersectionSize = getIntersectionSize(card.winningNumbers, card.numbers);
			return (1 << intersectionSize) >> 1;
		}),
		0,
		std::plus<>{});
}

int64_t solvePart2(std::string_view input)
{
	const auto cards = Parsing::parse(input);
	std::vector<int> cardsCount(cards.size(), 1);
	for (const auto& card : cards)
	{
		const int64_t intersectionSize = getIntersectionSize(card.winningNumbers, card.numbers);
		for (int64_t i = card.id; i < std::min(card.id + intersectionSize, ssize(cards)); ++i)
		{
			cardsCount[i] += cardsCount[card.id - 1];
		}
	}

	return std::ranges::fold_left(cardsCount, 0, std::plus<>{});
}

TEST(day04, test)
{
	EXPECT_EQ(solvePart1(day04::sample), 13);
	EXPECT_EQ(solvePart1(day04::input), 21485);

	EXPECT_EQ(solvePart2(day04::sample), 30);
	EXPECT_EQ(solvePart2(day04::input), 11024379);
}

} // anonymous namespace
