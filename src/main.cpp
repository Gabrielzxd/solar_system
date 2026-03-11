#include <iostream>
#include "../include/Vector.h"

int main() {
    Vector v1{1.0, 2.0};
    Vector v2{3.0, 4.0};

    Vector sum = v1 + v2;
    Vector diff = v1 - v2;
    Vector scaled = v1 * 2.0;
    double dot = v1 * v2;

    std::cout << "v1 + v2 = (" << sum.x << ", " << sum.y << ")\n";
    std::cout << "v1 - v2 = (" << diff.x << ", " << diff.y << ")\n";
    std::cout << "v1 * 2.0 = (" << scaled.x << ", " << scaled.y << ")\n";
    std::cout << "v1 * v2 (dot product) = " << dot << "\n";
    return 0;
}