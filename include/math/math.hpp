#ifndef __MATH__
#define __MATH__

#include <algorithm>
#include <ostream>
#include <cstdint>

namespace Ly::Math{

typedef double Float;
typedef uint64_t Integer;

enum class Sign : bool{
    Positive,
    Negative,

};

inline int make_number(Sign s) {
    return s == Sign::Positive ? 1 : -1;
}

inline std::ostream& operator<<(std::ostream& os, Sign s){
    auto flags = os.flags();
    if(s == Sign::Negative){
        os << '-';
    }
    else if(flags | std::ios_base::showpos){
        os << '+';
    }

    return os;
}

inline Sign operator!(Sign a){
    return a == Sign::Negative ? Sign::Positive : Sign::Negative;
}

inline Sign operator*(Sign a, Sign b){
    return a == b ? Sign::Positive : Sign::Negative;
}

inline Integer greatest_common_denominator(Integer a, Integer b){
    Integer max = std::max(a, b);
    Integer min = std::min(a, b);

    Integer dif = max - min;
    if(dif == min)
        return min;
    if(dif == max)
        return max;


    return greatest_common_denominator(min, dif);
}


}

#endif
