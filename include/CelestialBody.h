#include "Vector.h"

class CelestialBody {
private:
    Vector position;
    Vector velocity;
    double mass;
    double radius;
    Vector force_resultant;
public:
    CelestialBody(const Vector& position, const Vector& velocity, double mass, double radius);
    Vector getPosition() const;
    Vector getVelocity() const;
    double getMass() const;
    double getRadius() const;
};
