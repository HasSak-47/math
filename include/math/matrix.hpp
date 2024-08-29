#ifndef __MATH_MATRIX_HPP__
#define __MATH_MATRIX_HPP__

#include <sstream>
#include <cstddef>

namespace Ly::Math{

template<size_t WIDTH, size_t HEIGHT, typename T>
class MatrixT;

template<size_t WIDTH, size_t HEIGHT, typename T>
class MatrixT{
private:
    T _data[WIDTH][HEIGHT] = {};
public:
	T& get(size_t i , size_t j) {
		if(i >= WIDTH){
			std::stringstream ss;
			ss << "MatrixT::get(i, j) i >= WIDTH";
			throw std::runtime_error(ss.str());
		}

		if(j >= HEIGHT){
			std::stringstream ss;
			ss << "MatrixT::get(i, j) j >= HEIGHT";
			throw std::runtime_error(ss.str());
		}

		return this->_data[i][j];
	}

	T& get(size_t i , size_t j) const{
		if(i >= WIDTH){
			std::stringstream ss;
			ss << "MatrixT::get(i, j) i >= WIDTH";
			throw std::runtime_error(ss.str());
		}

		if(j >= HEIGHT){
			std::stringstream ss;
			ss << "MatrixT::get(i, j) j >= HEIGHT";
			throw std::runtime_error(ss.str());
		}

		return this->_data[i][j];
	}

    friend MatrixT operator+(const MatrixT& a, const MatrixT& b);

    template<size_t P, size_t N, size_t M, size_t Q>
    friend MatrixT<N, M, T> operator*(const MatrixT<P, N, T>& a, const MatrixT<M, Q, T>& b);
};

template<size_t WIDTH, size_t HEIGHT, typename T>
inline MatrixT<WIDTH, HEIGHT, T> operator+(const MatrixT<WIDTH, HEIGHT, T>& a, const MatrixT<WIDTH, HEIGHT, T>& b){
    MatrixT<WIDTH, HEIGHT, T> n = {};
    for(size_t i = 0; i < WIDTH; ++i)
        for(size_t j = 0; j < WIDTH; ++j)
            n.get(i, j) = a.get(i, j) + b.get(i, j);

    return n;
}

template<size_t M, size_t N, size_t P, typename T>
inline MatrixT<N, M, T> operator*(const MatrixT<M, N, T>& a, const MatrixT<N, P, T>& b){
    MatrixT<M, P, T> n = {};
    for(size_t i = 0; i < M; ++i){
        for(size_t j = 0; j < P; ++j){
            for(size_t k = 0; k < N; ++k){
                n.get(i, j) = a.get(i, k) * b.get(k, j);
            }
        }
    }

    return n;
}

template<size_t WIDTH, size_t HEIGHT, typename T>
inline std::ostream& operator<<(std::ostream& os, const MatrixT<WIDTH, HEIGHT, T>& mat){
	for(size_t j = 0; j < HEIGHT; ++j){
		for(size_t i = 0; i < WIDTH; ++i){
			os << mat.get_const(i, j) << ' ';
		}
		os << std::endl;
	}

    return os;
}

template<size_t LENGHT, typename T>
using VectorT = MatrixT<1, LENGHT, T>;

}

#endif
