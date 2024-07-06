#include <algorithm>
#include <ranges>

namespace Utils
{

constexpr auto sum(std::ranges::range auto&& range)
{
	return std::ranges::fold_left(
		range, std::ranges::range_value_t<decltype(range)>{}, std::plus{});
}

} // namespace Utils
