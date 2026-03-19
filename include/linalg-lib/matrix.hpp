#pragma once
#include <array>
#include "vector.hpp"

namespace linalg {
    template <std::size_t N, std::size_t M, typename T = double>
    class Matrix{
        private:
            std::array<std::array<T, M>, N> data;
        public:
            Matrix() = default;
            Matrix(std::initializer_list<std::initializer_list<T>> list){
                std::size_t i = 0;
                for (auto it = list.begin(); it != list.end() && i < N; it++, i++){
                    std::size_t j = 0;
                    for (auto jt = it->begin(); jt != it->end() && j < M; jt++, j++){
                        data[i][j] = *jt;
                    }
                }
            }

            std::pair<std::size_t, std::size_t> size() const{ return {N, M}; }

            T& operator()(std::size_t i, std::size_t j){ return data[i][j]; }

            const T& operator()(std::size_t i, std::size_t j) const { return data[i][j];}

            Matrix<N, M, T> operator+(const Matrix<N, M, T>& other) const {
                Matrix<N, M, T> result;
                for (std::size_t i = 0; i < N; i++) {
                    for (std::size_t j = 0; j < M; j++) {
                        result.data[i][j] = this->data[i][j] + other.data[i][j];
                    }
                }
                return result;
            }

            Matrix<N, M, T> operator-(const Matrix<N, M, T>& other) const {
                Matrix<N, M, T> result;
                for (std::size_t i = 0; i < N; i++) {
                    for (std::size_t j = 0; j < M; j++) {
                        result.data[i][j] = this->data[i][j] - other.data[i][j];
                    }
                }
                return result;
            }

            Matrix<N, M, T> operator*(const T& scalar) const {
                Matrix<N, M, T> result;
                for (std::size_t i = 0; i < N; i++) {
                    for (std::size_t j = 0; j < M; j++) {
                        result.data[i][j] = this->data[i][j] * scalar;
                    }
                }
                return result;
            }

            template <std::size_t P>
            Matrix<N, P, T> operator*(const Matrix<M, P, T>& other) const {
                Matrix<N, P, T> result;
                for (std::size_t i = 0; i < N; i++) {
                    for (std::size_t j = 0; j < P; j++) {
                        T sum = 0;
                        for(std::size_t k = 0; k < M; k++){
                            sum += this->data[i][k] * other(k, j); 
                        }
                        result(i, j) = sum;
                    }
                }
                return result;
            }

            Matrix<M, N, T> transpose() const{
                Matrix<M, N, T> result;
                for (std::size_t i = 0; i < N; i++){
                    for (std::size_t j = 0; j < M; j++){
                        result.data[j][i] = this->data[i][j];
                    }
                }
                return result;
            }

            static Matrix<N, N, T> identity(){
                Matrix<N, N, T> result;
                for (std::size_t i = 0; i < N; i++){
                    for (std::size_t j = 0; j < N; j++){
                        result.data[i][j] = (i == j) ? 1 : 0;
                    }
                }
                return result;
            }

            static Matrix<4, 4, T> translation(T dx, T dy, T dz){
                Matrix<4, 4, T> mat = identity();
                mat(0, 3) = dx;
                mat(1, 3) = dy;
                mat(2, 3) = dz;
                return mat;
            }
            
            static Matrix<4, 4, T> scale(T sx, T sy, T sz) {
                Matrix<4, 4, T> mat = identity();
                mat(0, 0) = sx;
                mat(1, 1) = sy;
                mat(2, 2) = sz;
                return mat;
            }

            static Matrix<4, 4, T> rotationX(T theta){
                Matrix<4, 4, T> mat = identity();
                mat(1, 1) = std::cos(theta);
                mat(1, 2) = - std::sin(theta);
                mat(2, 1) = std::sin(theta);
                mat(2, 2) = std::cos(theta);
                return mat;
            }

            static Matrix<4, 4, T> rotationY(T theta){
                Matrix<4, 4, T> mat = identity();
                mat(0, 0) = std::cos(theta);
                mat(0, 2) = std::sin(theta);
                mat(2, 0) = - std::sin(theta);
                mat(2, 2) = std::cos(theta);
                return mat;
            }

            static Matrix<4, 4, T> rotationZ(T theta){
                Matrix<4, 4, T> mat = identity();
                mat(0, 0) = std::cos(theta);
                mat(0, 1) = - std::sin(theta);
                mat(1, 0) = std::sin(theta);
                mat(1, 1) = std::cos(theta);
                return mat;
            }
    };

    template <std::size_t N, std::size_t M, typename T>
    Vector<N, T> operator*(const Matrix<N, M, T>& mat, const Vector<M, T>& vec) {
        Vector<N, T> result = Vector<N, T>::zero();
        for (std::size_t i = 0; i < N; i++) {
            for (std::size_t j = 0; j < M; j++) {
                result[i] += mat(i, j) * vec[j];
            }
        }
        return result;
    }
}