#include "physics.h"
#include "CelestialBody.h"
#include <cmath>

State State::operator+(const State& other) const {
    State result;
    size_t n = pos.size();
    result.pos.resize(n);
    result.vel.resize(n);
    for (size_t i = 0; i < n; i++) {
        result.pos[i] = this->pos[i] + other.pos[i];
        result.vel[i] = this->vel[i] + other.vel[i];
    }
    return result;
}

State State::operator*(double scalar) const {
    State result;
    size_t n = pos.size();
    result.pos.resize(n);
    result.vel.resize(n);
    for (size_t i = 0; i < n; i++) {
        result.pos[i] = this->pos[i] * scalar;
        result.vel[i] = this->vel[i] * scalar;
    }
    return result;
}

State derivative(const State& s, const std::vector<double>& masses) {
    size_t n = masses.size();
    State ds;
    ds.pos.resize(n);
    ds.vel.resize(n);


    for (size_t i = 0; i < n; i++) {
        ds.pos[i] = s.vel[i]; 

        linalg::Vector<3> totalAccel = linalg::Vector<3>::zero();

        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;

            linalg::Vector<3> r_vec = s.pos[j] - s.pos[i];
            double dist = r_vec.norm();

            if (dist > 0.0001) {
                double accel_mag = (G * masses[j]) / (dist * dist);
                
                totalAccel = totalAccel + r_vec * (accel_mag / dist);
            }
        }
        ds.vel[i] = totalAccel; 
    }
    return ds;
}

void stepRK4(State& state, const std::vector<double>& masses, double h) {
    State k1 = derivative(state, masses);
    State k2 = derivative(state + (k1 * (h * 0.5)), masses);
    State k3 = derivative(state + (k2 * (h * 0.5)), masses);
    State k4 = derivative(state + (k3 * h), masses);

    size_t n = state.pos.size();
    for (size_t i = 0; i < n; i++) {
        state.pos[i] = state.pos[i] + (k1.pos[i] + k2.pos[i]*2.0 + k3.pos[i]*2.0 + k4.pos[i]) * (h / 6.0);
        state.vel[i] = state.vel[i] + (k1.vel[i] + k2.vel[i]*2.0 + k3.vel[i]*2.0 + k4.vel[i]) * (h / 6.0);
    }
}