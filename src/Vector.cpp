#include "../include/Vector.h"
#include <math.h>

Vector Vector::operator+(const Vector& other) const {
    return {this->x + other.x, this->y + other.y};
}

Vector Vector::operator-(const Vector& other) const{
    return {this->x - other.x, this->y - other.y};
}

Vector Vector::operator*(double scalar) const{
    return {this->x * scalar, this->y * scalar};
}

double Vector::operator*(const Vector& other) const{
    return this->x*other.x + this->y*other.y;
}

double Vector::magnitude() const{
    return sqrt(this->x*this->x + this->y*this->y);
}