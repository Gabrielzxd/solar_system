#include <iostream>
#include <cassert>
#include <cmath>
#include "../include/linalg-lib/vector.hpp"

const double EPS = 1e-9;

using Vec3 = linalg::Vector<3>;

void test_sum(){
    Vec3 v1 = {1.0, 2.0, 3.0};
    Vec3 v2 = {4.0, 5.0, 6.0};
    Vec3 v3 = v1 + v2;
    assert(std::abs(v3[0] - 5.0) < EPS);
    assert(std::abs(v3[1] - 7.0) < EPS);
    assert(std::abs(v3[2] - 9.0) < EPS);
}

void test_sum_edge_case(){
    Vec3 v1 = {0.0, 2.0, -9.0};
    Vec3 v2 = {0.0, -2.0, 9.0};
    Vec3 v3 = v1 + v2;
    assert(std::abs(v3[0] - 0.0) < EPS);
    assert(std::abs(v3[1] - 0.0) < EPS);
    assert(std::abs(v3[2] - 0.0) < EPS);
}

int main(){
    test_sum();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}