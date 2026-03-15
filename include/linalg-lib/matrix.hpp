#pragma once
#include <array>

namespace linalg {
    template <std::size_t N, std::size_t M, typename T = double>
    class Matrix{
        private:
            std::array<std::array<T, M>, N> data;
        public:
            Matrix() default;
            Matrix(std::initializer_list<std::initializer_list<T>> list){
                std::size_t i = 0;
                for (auto it = list.begin(); it != list.end() && i < N; it++, i++){
                    std::size_t j = 0;
                    for (auto jt = it->begin(); jt != it->end() && j < M; jt++, j++){
                        data[i][j] = *jt;
                    }
                }
            }

            std::pair<std::size_t, std::size_t> size() const{
                return {N, M};
            }

            T& operator()(std::size_t i, std::size_t j){
                return data[i][j];
            }

            const T& operator()(std::size_t i, std::size_t j) const {
                return data[i][j];
            }

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

            template <std::size_t, std::size_t, typename> friend class Matrix;
            Matrix<N, P, T> operator*(const Matrix<M, P, T>& other) const{
                Matrix<N, P, T> result;
                for (std::size_t i = 0; i < N; i++){
                    for (std::size_t j = 0; j < P; j++){
                        T sum = 0;
                        for(std::size_t k = 0; k < M; k++){
                            sum += this->data[i][k] * other.data[k][j];
                        }
                        result.data[i][j] = sum;
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
    };
}