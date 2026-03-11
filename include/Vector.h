struct Vector{
    double x, y;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& other) const; // Dot product
};