#pragma once
#include "linalg-lib/vector.hpp"
#include <vector>

struct State {
    std::vector<linalg::Vector<3>> pos;
    std::vector<linalg::Vector<3>> vel;

    State operator+(const State& other) const;
    State operator*(double scalar) const;
};

State derivative(const State& s, const std::vector<double>& masses);
void stepRK4(State& state, const std::vector<double>& masses, double h);
