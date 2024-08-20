#ifndef __MATH_NUMBER_HPP__
#define __MATH_NUMBER_HPP__

#include <ostream>

#include "./math.hpp"

// god so much of this is inlined
// this should not continue
namespace Ly::Math{


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
    return a == Sign::Positive ? Sign::Positive : Sign::Negative;
}

class SignedNumber{
protected:
    Sign _s = Sign::Positive;
public:
    SignedNumber() {}
    SignedNumber(Sign s) : _s(s) {}
    virtual ~SignedNumber() {};
    virtual Float tof64() = 0;
    void set_abs() {
        this->_s = Sign::Positive;
    }
};

class NNumber : public SignedNumber{
protected:
    Integer _n = 0;
public:
    NNumber(){};
    NNumber(Integer n, Sign s = Sign::Positive) : _n(n), SignedNumber(s){}

    ~NNumber() {}
    Float tof64() override { return _n; }

    friend std::ostream& operator<<(std::ostream& os, NNumber n);
};

inline std::ostream& operator<<(std::ostream& os, NNumber n){
    os << n._s << n._n;
    return os;
}

#define NNumberOverride(op, p)\
NNumber op(NNumber a, NNumber b){\
    return a p b;\
}\

inline NNumberOverride(operator+, +);
inline NNumberOverride(operator-, -);
inline NNumberOverride(operator*, *);
inline NNumberOverride(operator/, /);

#undef NNumberOverride

class QNumber: public SignedNumber{
protected:
    Integer _n = 0, _d = 1;
public:
    QNumber(){}
    QNumber(Integer n, Integer d = 1, Sign s = Sign::Positive): _n(n), _d(d), SignedNumber(s) {}
    Float tof64() override { return (float)this->_n / this->_d; }
    friend std::ostream& operator<<(std::ostream& os, QNumber n);
};

inline std::ostream& operator<<(std::ostream& os, QNumber n){
    os << n._s << n._n << " / " << n._d;
    return os;
}

inline QNumber operator+(QNumber a, QNumber b){
    return a;
}

}

#endif
