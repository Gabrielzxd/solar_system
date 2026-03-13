#include "../include/CelestialBody.h"

constexpr double PI = 3.14159;
constexpr double G = 4 * PI * PI;

CelestialBody::CelestialBody(std::string name, const Vector& position, const Vector& velocity, double mass, double radius, Color RGB) {
    this->name = name;
    this->position = position;
    this->velocity = velocity;
    this->mass = mass;
    this->radius = radius;
    this->color = RGB;
    this->force_accumulator = {0.0, 0.0};
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

Vector CelestialBody::getPosition() const {
    return this->position;
}

void CelestialBody::setPosition(const Vector& new_position) {
    this->position = new_position;
}

Vector CelestialBody::getVelocity() const {
    return this->velocity;
}

void CelestialBody::setVelocity(const Vector& new_velocity) {
    this->velocity = new_velocity;
}

Color CelestialBody::getColor() const {
    return this->color;
}

Vector CelestialBody::getGravitationalForce(const CelestialBody& other) const {
    Vector r_vec = other.getPosition() - this->getPosition();
    double dist = r_vec.magnitude();

    if (dist < 0.0001) return {0.0, 0.0};

    double force_mag = (G * this->getMass() * other.getMass()) / (dist * dist);
    Vector force_vec = r_vec * (force_mag / dist);
    return force_vec;
}

Vector CelestialBody::getAcceleration(const CelestialBody& other) const {
    Vector force = getGravitationalForce(other);
    return force * (1.0 / this->getMass());
}

void CelestialBody::attract(const CelestialBody& other) {
    this->force_accumulator = this->force_accumulator + getGravitationalForce(other);
}

void CelestialBody::update(double dt) {
    Vector acceleration = this->force_accumulator * (1.0 / this->getMass());
    this->velocity = this->velocity + acceleration * dt;
    this->position = this->position + this->velocity * dt;
    this->force_accumulator = {0.0, 0.0};
}