#pragma once
#include "../include/linalg-lib/vector.hpp"
#include <iostream>
#include <TextureLoader.h>

constexpr double PI = 3.14159;
constexpr double G = 4 * PI * PI;

using Vec3 = linalg::Vector<3>;

struct Color{
    float r, g, b;
};

class CelestialBody {
private:
    std::string name;
    Vec3 position;
    Vec3 velocity;
    double mass;
    double radius;
    Color color;
//    GLuint textureID;

public:
    CelestialBody(std::string name, const Vec3& position, const Vec3& velocity, double mass, double radius, Color RGB);
    Vec3 getPosition() const;
    void setName(const std::string& new_name);
    std::string getName() const;
    void setPosition(const Vec3& new_position);
    Vec3 getVelocity() const;
    void setVelocity(const Vec3& new_velocity);
    double getMass() const;
    double getRadius() const;
    Color getColor() const;
//    GLuint getTextureID() const;
};
