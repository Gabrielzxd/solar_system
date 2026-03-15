#include "../include/CelestialBody.h"

constexpr double PI = 3.14159;
constexpr double G = 4 * PI * PI;

CelestialBody::CelestialBody(std::string name, const Vec2& position, const Vec2& velocity, double mass, double radius, Color RGB, const std::string& texturePath) 
    : name(name), position(position), velocity(velocity), mass(mass), radius(radius), force_accumulator(Vec2::zero()), color(RGB) 
{
    this->textureID = loadTexture(texturePath);
}

std::string CelestialBody::getName() const {
    return this->name;
}

void CelestialBody::setName(const std::string& new_name) {
    this->name = new_name;
}

double CelestialBody::getMass() const {
    return this->mass;
}

double CelestialBody::getRadius() const {
    return this->radius;
}

Vec2 CelestialBody::getPosition() const {
    return this->position;
}

void CelestialBody::setPosition(const Vec2& new_position) {
    this->position = new_position;
}

Vec2 CelestialBody::getVelocity() const {
    return this->velocity;
}

void CelestialBody::setVelocity(const Vec2& new_velocity) {
    this->velocity = new_velocity;
}

Color CelestialBody::getColor() const {
    return this->color;
}

Vec2 CelestialBody::getGravitationalForce(const CelestialBody& other) const {
    Vec2 r_vec = other.getPosition() - this->getPosition();
    double dist = r_vec.norm();

    if (dist < 0.0001) return {0.0, 0.0};

    double force_mag = (G * this->getMass() * other.getMass()) / (dist * dist);
    Vec2 force_vec = r_vec * (force_mag / dist);
    return force_vec;
}

Vec2 CelestialBody::getAcceleration(const CelestialBody& other) const {
    Vec2 force = getGravitationalForce(other);
    return force * (1.0 / this->getMass());
}

void CelestialBody::attract(const CelestialBody& other) {
    this->force_accumulator = this->force_accumulator + getGravitationalForce(other);
}

void CelestialBody::update(double dt) {
    Vec2 acceleration = this->force_accumulator * (1.0 / this->getMass());
    this->velocity = this->velocity + acceleration * dt;
    this->position = this->position + this->velocity * dt;
    this->force_accumulator = {0.0, 0.0};
}

GLuint CelestialBody::getTextureID() const {
    return textureID;
}