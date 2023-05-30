#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

#include "../include/board.h"

template<class T, size_t... Ns> struct foo;

template<class T, size_t N0, size_t... Ns>
struct foo<T, N0, Ns...> {
    using type = std::array<typename foo<T, Ns...>::type, N0>;
};

template<class T>
struct foo<T> {
    using type = T;
};

template<class T, size_t... Ns>
using multiarray_t = typename foo<T, Ns...>::type;


class Pattern
{
public:
    Pattern(std::vector<int> chosen_positions);

    float get_pattern_value(Board& board);

    void update_pattern_value(Board& board, float target_value, float learning_rate);

    // member variables
    multiarray_t<float, 12, 12, 12, 12, 12, 12> table;

    std::vector<int> chosen_positions;
};