#include <limits>
#include <print>

[[nodiscard]]
bool WillOverflow(int x)
{
    return x + 1 < x;
}

int main()
{
    auto result = WillOverflow(std::numeric_limits<int>::max());
    std::println("Result is {}", result);
    return 0;
}