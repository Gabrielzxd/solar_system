#include <iostream>
#include <vector>
#include "../include/CelestialBody.h"

int main() {
    std::vector<CelestialBody> bodies;
    bodies.emplace_back(Vector{0.0, 0.0}, Vector{0.0, 0.0}, 100.0, 1.0); //Sol
    bodies.emplace_back(Vector{10.0, 0.0}, Vector{0.0, 3.16}, 1.0, 0.1); //Terra

    double dt = 0.01;

    for (int passo = 0; passo < 1000; passo++){
        for(size_t i = 0; i < bodies.size(); i++){
            for(size_t j = 0; j < bodies.size(); j++){
                if(i != j){
                    bodies[i].attract(bodies[j]);
                }
            }
        }
        for (auto& body : bodies) {
            body.update(dt);
        }
        if (passo % 10 == 0) {
        Vector p = bodies[1].getPosition();
        std::cout << "Pos: (" << p.x << ", " << p.y << ") | Dist: " << p.magnitude() << "\n";
    }
    }
}