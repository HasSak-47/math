#include <iostream>
#include <math/math.hpp>
#include <math/number.hpp>
#include <math/test.hpp>
#include <ostream>

using namespace Ly::Math;

#include <cstring> 

int main(const int argc, const char** argv){
    if(argc >= 2 && strcmp(argv[1], "test") == 0){
        std::cout << "testing numbers...\n";
        bool error = test_numbers();
        if(error){
            std::cout << "numbers failed!!" << std::endl;
        }
        else{
            std::cout << "numbers okay!!" << std::endl;
        }
    }
    return 0;
}
