#include <vector>
#include "../include/CelestialBody.h"
#include "../include/linalg-lib/vector.hpp"

CelestialBody::CelestialBody(std::string name, const Vec3& position, const Vec3& velocity, double mass, double radius, Color RGB) 
    : name(name), position(position), velocity(velocity), mass(mass), radius(radius), color(RGB) 
{
//    this->textureID = loadTexture(texturePath);
}

std::string CelestialBody::getName() const { return this->name; }

void CelestialBody::setName(const std::string& new_name) { this->name = new_name; }

double CelestialBody::getMass() const { return this->mass; }

double CelestialBody::getRadius() const { return this->radius; }

Vec3 CelestialBody::getPosition() const { return this->position; }

void CelestialBody::setPosition(const Vec3& new_position) { this->position = new_position; }

Vec3 CelestialBody::getVelocity() const { return this->velocity; }

void CelestialBody::setVelocity(const Vec3& new_velocity) { this->velocity = new_velocity; }

Color CelestialBody::getColor() const { return this->color; }

//GLuint CelestialBody::getTextureID() const {
//    return textureID;
//}