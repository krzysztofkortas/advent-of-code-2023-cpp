#include "inputs/day01.h"

#include <cassert>
#include <ranges>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

constexpr int calculateTotalCalibration(std::string_view input)
{
	return Utils::sum(input | vw::split('\n') | vw::transform([](auto&& line) {
		auto digits = line | vw::filter([](char c) { return c >= '0' && c <= '9'; });
		assert(!digits.empty());
		return std::stoi(std::string{digits.front(), digits.back()});
	}));
}

constexpr int calculatePart1(std::string_view input)
{
	return calculateTotalCalibration(input);
}

constexpr void replace(std::string& str, std::string_view pattern, std::string_view replacement)
{
	str = str | vw::split(pattern) | vw::join_with(replacement) | rng::to<std::string>();
}

constexpr std::string getModifiedInput(std::string_view str)
{
	std::string result{str};

	replace(result, "one", "one1one");
	replace(result, "two", "two2two");
	replace(result, "three", "three3three");
	replace(result, "four", "four4four");
	replace(result, "five", "five5five");
	replace(result, "six", "six6six");
	replace(result, "seven", "seven7seven");
	replace(result, "eight", "eight8eight");
	replace(result, "nine", "nine9nine");

	return result;
}

constexpr int calculatePart2(std::string_view input)
{
	return calculateTotalCalibration(getModifiedInput(input));
}

TEST(day01, test)
{
	EXPECT_EQ(calculatePart1(day01::samplePart1), 142);
	EXPECT_EQ(calculatePart2(day01::samplePart2), 281);

	EXPECT_EQ(calculatePart1(day01::input), 54601);
	EXPECT_EQ(calculatePart2(day01::input), 54078);
}

} // anonymous namespace
