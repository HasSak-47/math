#ifndef __MATH__
#define __MATH__

#include <algorithm>
#include <cstdint>

namespace Ly::Math{

typedef double Float;
typedef uint64_t Integer;

enum class Sign{
    Positive,
    Negative,
};

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
