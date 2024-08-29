#include "math/matrix.hpp"
#include <iostream>
#include <math/math.hpp>
#include <math/number.hpp>
#include <math/test.hpp>
#include <ostream>

using namespace Ly::Math;

#include <cstring> 

#define WIDTH 3
#define HEIGHT 3

int main(const int argc, const char** argv){
    if(argc >= 2 && strcmp(argv[1], "test") == 0){
        std::cout << "testing numbers...\n";
        bool error = test_numbers();
        if(error)
            std::cout << "numbers failed!!" << std::endl;
        else
            std::cout << "numbers okay!!" << std::endl;
        std::cout << "testing matrix...\n";
        error = test_matrix();
        if(error)
            std::cout << "numbers failed!!" << std::endl;
        else
            std::cout << "numbers okay!!" << std::endl;
    }

    MatrixT<WIDTH, HEIGHT, float> source_mat = {};
    for(size_t i = 0; i < WIDTH; ++i){
        for(size_t j = 0; j < HEIGHT; ++j){
            source_mat.get(i, j) = 1;
        }
    }





    return 0;
}
