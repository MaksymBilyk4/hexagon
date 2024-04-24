#include "./removeFromVector.hpp"
#include <vector>

template<typename T>
auto removeFromVector(std::vector<T> &vec, T const &context) -> void {
    auto iter = std::ranges::find_if(vec.begin(), vec.end(), [context](auto &el) -> bool { return el == context; });
    vec.erase(iter);
}