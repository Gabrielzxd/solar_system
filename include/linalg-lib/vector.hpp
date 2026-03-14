#pragma once
#include <cmath>
#include <array>
#include <initializer_list>

namespace linalg {
    template <std::size_t N, typename T = double>
    class Vector {
    private:
        std::array<T, N> data;

    public:
        Vector() = default;
        Vector(std::initializer_list<T> list) {
            std::size_t i = 0;
            for (auto it = list.begin(); it != list.end() && i < N; ++it, ++i) {
                data[i] = *it;
            }
        }

        std::size_t size() const { return N; }
        
        T operator[](std::size_t i) const { return data[i]; }
        T& operator[](std::size_t i) { return data[i]; }

        Vector<N, T> operator+(const Vector<N, T>& other) const {
            Vector<N, T> result;
            for(std::size_t i = 0; i < N; i++) {
                result.data[i] = this->data[i] + other.data[i];
            }
            return result;
        }

        Vector<N, T> operator-(const Vector<N, T>& other) const {
            Vector<N, T> result;
            for(std::size_t i = 0; i < N; i++) {
                result.data[i] = this->data[i] - other.data[i];
            }
            return result;
        }

        Vector<N, T> operator*(const T& scalar) const {
            Vector<N, T> result;
            for(std::size_t i = 0; i < N; i++) {
                result.data[i] = this->data[i] * scalar;
            }
            return result;
        }

        T dot(const Vector<N, T>& other) const {
            T result = 0;
            for (std::size_t i = 0; i < N; i++) {
                result += this->data[i] * other.data[i];
            }
            return result;
        }

        double norm() const {
            return std::sqrt(static_cast<double>(this->dot(*this)));
        }

        double angle(const Vector<N, T>& other) const {
            double n1 = this->norm();
            double n2 = other.norm();
            double norms_prod = n1 * n2;

            if (norms_prod == 0) return 0.0;

            double cos_theta = static_cast<double>(this->dot(other)) / norms_prod;

            if (cos_theta > 1.0) cos_theta = 1.0;
            else if (cos_theta < -1.0) cos_theta = -1.0;

            return std::acos(cos_theta);
        }

        void set_zero() {
            for(auto& val : data) val = 0;
        }

        static Vector<N, T> zero() {
            Vector<N, T> result;
            result.set_zero();
            return result;
        }
    };

    template <std::size_t N, typename T>
    Vector<N, T> operator*(const T& scalar, const Vector<N, T>& v) {
        return v * scalar;
    }
}