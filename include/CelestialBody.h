#include "Vector.h"

class CelestialBody {
private:
    Vector position;
    Vector velocity;
    double mass;
    double radius;
    Vector force_accumulator;
public:
    CelestialBody();
    CelestialBody(const Vector& position, const Vector& velocity, double mass, double radius);
    Vector getPosition() const;
    void setPosition(const Vector& new_position);
    Vector getVelocity() const;
    void setVelocity(const Vector& new_velocity);
    double getMass() const;
    double getRadius() const;
    void attract(const CelestialBody& other);
    Vector getGravitationalForce(const CelestialBody& other) const;
    Vector getAcceleration(const CelestialBody& other) const;
    void update(double dt);
};
