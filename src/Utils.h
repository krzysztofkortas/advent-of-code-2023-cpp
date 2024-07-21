#include <algorithm>
#include <functional>
#include <ranges>

namespace Utils
{

constexpr auto sum(std::ranges::range auto&& range)
{
	return std::ranges::fold_left_first(range, std::plus{}).value();
}

constexpr auto multiply(std::ranges::range auto&& range)
{
	return std::ranges::fold_left_first(range, std::multiplies{}).value();
}

} // namespace Utils
