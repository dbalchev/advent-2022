#pragma once

#include <functional>
#include <tuple>

// template<typename T1, typename T2>
// struct std::hash<std::tuple<T1, T2> > {
//     std::size_t operator()(const std::tuple<T1, T2>& p) const noexcept {
//         auto [x, y] = p;
//         return std::hash<T1>{}(x) * 91 + std::hash<T2>{}(y);
//     }
// };

template <typename T>
std::size_t __gen_hash(const T &x) {
    auto hash = std::hash<T>{}(x);
    // std::cout << "get_hash of " << x << " is " << hash << std::endl;
    return hash;
}

template<size_t I>
struct __tuple_hash{
    template<typename TupleType>
    std::size_t operator()(const TupleType& p) const noexcept {
        const size_t idx = std::tuple_size<TupleType>::value - I;
        const auto & current = std::get<idx>(p);
        return __gen_hash(current) + 91 * __tuple_hash<I - 1>{}(p);
    }
};

template<>
struct __tuple_hash<0> {
        template<typename TupleType>
    std::size_t operator()(const TupleType& p) const noexcept {
        return 0;
    }
};

template<typename... Ts>
struct std::hash<std::tuple<Ts...> > {
    typedef std::tuple<Ts...> TupleType;
    std::size_t operator()(const std::tuple<Ts...>& p) const noexcept {
        auto hash = __tuple_hash<std::tuple_size<TupleType>::value>{}(p);
        // std::cout << "hash = " << hash << std::endl;
        return hash;
    }
};
