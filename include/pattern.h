#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <functional>

#include "../include/board.h"

template <size_t N>
struct MultiArrayHelper
{
    template <class T>
    constexpr std::array<T, N> operator*(T);
};

template <class T, size_t... Ns>
using MultiArray = decltype((MultiArrayHelper<Ns>{} * ... * T{}));

template <class T>
struct StdArrayTraiter : std::false_type
{
};

template <class T, size_t N>
struct StdArrayTraiter<std::array<T, N>> : std::true_type
{
    static constexpr size_t kSize = N;
};

template <class T, typename = void>
struct MultiArrayExpander
{
    using ElementType = T;

    static constexpr size_t kDimension = 0;
};

template <class T>
struct MultiArrayExpander<T, std::enable_if_t<StdArrayTraiter<T>::value>>
{
    using ElementExpander =
        MultiArrayExpander<std::remove_reference_t<decltype(std::declval<T>()[0])>>;

    using ElementType = typename ElementExpander::ElementType;

    static constexpr size_t kSize = StdArrayTraiter<T>::kSize;
    static constexpr size_t kDimension = ElementExpander::kDimension + 1;
};

template <class T, class Index, class... Args>
constexpr decltype(auto) MultiArrayAt(T &array, Index index, Args... indexes)
{
    using Expander = MultiArrayExpander<T>;
    static_assert((sizeof...(Args) + 1) == Expander::kDimension);
    static_assert(std::is_convertible_v<Index, size_t>);

    if constexpr (sizeof...(Args))
    {
        return MultiArrayAt(array[index], indexes...);
    }
    else
    {
        return array[index];
    }
}

template <class T>
constexpr void MultiArrayForEach(
    T &array, const std::function<void(typename MultiArrayExpander<T>::ElementType &)> &operation)
{
    if (!operation)
    {
        return;
    }

    using Expander = MultiArrayExpander<T>;

    if constexpr (Expander::kDimension)
    {
        for (auto &element : array)
        {
            MultiArrayForEach(element, operation);
        }
    }
    else
    {
        operation(array);
    }
}

class Pattern
{
public:
    Pattern(std::array<int, 6> basic_pattern_positions);

    float get_pattern_value(Board &board);

    float update_pattern_value(Board &board, float adjust);

    // member variables
    MultiArray<float, 12, 12, 12, 12, 12, 12> table;

    std::array<std::array<int, 6>, 8> pattern_positions;
    
    void save_table(std::string path);
    void load_table(std::string path);
};