#pragma once

#include <functional>
#include <tuple>

template<typename T1, typename T2>
struct std::hash<std::tuple<T1, T2> > {
    std::size_t operator()(const std::tuple<T1, T2>& p) const noexcept {
        auto [x, y] = p;
        return std::hash<T1>{}(x) * 91 + std::hash<T2>{}(y);
    }
};