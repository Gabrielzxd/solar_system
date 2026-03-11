#include "../include/CelestialBody.h"

CelestialBody::CelestialBody(const Vector& position, const Vector& velocity, double mass, double radius) {
    this->position = position;
    this->velocity = velocity;
    this->mass = mass;
    this->radius = radius;
    this->force_resultant = {0.0, 0.0};
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

Vector CelestialBody::getVelocity() const {
    return this->velocity;
}