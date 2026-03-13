#pragma once
#include "Vector.h"
#include <iostream>

struct Color{
    float r, g, b;
};

class CelestialBody {
private:
    std::string name;
    Vector position;
    Vector velocity;
    double mass;
    double radius;
    Vector force_accumulator;
    Color color;

public:
    CelestialBody(std::string name, const Vector& position, const Vector& velocity, double mass, double radius, Color RGB);
    Vector getPosition() const;
    void setName(const std::string& new_name);
    std::string getName() const;
    void setPosition(const Vector& new_position);
    Vector getVelocity() const;
    void setVelocity(const Vector& new_velocity);
    double getMass() const;
    double getRadius() const;
    void attract(const CelestialBody& other);
    Vector getGravitationalForce(const CelestialBody& other) const;
    Vector getAcceleration(const CelestialBody& other) const;
    void update(double dt);
    Color getColor() const;
};
