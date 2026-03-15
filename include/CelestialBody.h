#pragma once
#include "../include/linalg-lib/vector.hpp"
#include <iostream>
#include <TextureLoader.h>

using Vec2 = linalg::Vector<2>;

struct Color{
    float r, g, b;
};

class CelestialBody {
private:
    std::string name;
    Vec2 position;
    Vec2 velocity;
    double mass;
    double radius;
    Vec2 force_accumulator;
    Color color;
    GLuint textureID;

public:
    CelestialBody(std::string name, const Vec2& position, const Vec2& velocity, double mass, double radius, Color RGB, const std::string& texturePath);
    Vec2 getPosition() const;
    void setName(const std::string& new_name);
    std::string getName() const;
    void setPosition(const Vec2& new_position);
    Vec2 getVelocity() const;
    void setVelocity(const Vec2& new_velocity);
    double getMass() const;
    double getRadius() const;
    void attract(const CelestialBody& other);
    Vec2 getGravitationalForce(const CelestialBody& other) const;
    Vec2 getAcceleration(const CelestialBody& other) const;
    void update(double dt);
    Color getColor() const;
    GLuint getTextureID() const;
};
