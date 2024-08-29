#ifndef __MATH_NUMBER_HPP__
#define __MATH_NUMBER_HPP__

#include <cmath>
#include <ostream>
#include <sstream>
#include <stdexcept>

#include "./math.hpp"

// god so much of this is inlined
// this should not continue
namespace Ly::Math{

class SignedNumber{
protected:
    Sign _s = Sign::Positive;
public:
    SignedNumber() {}
    SignedNumber(Sign s) : _s(s) {}
    virtual ~SignedNumber() {};
    virtual Float to_float() = 0;
    virtual Integer to_integer() = 0;
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
    Float to_float() override { return _n; }
    Integer to_integer() override { return _n; }

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
    enum Flags {
        Infinity,
    } _flags;
    Integer _n, _d;
public:
    QNumber(Integer n = 0, Integer d = 1, Sign s = Sign::Positive): _n(n), _d(d), SignedNumber(s) {
        if(d == 0){
            std::stringstream ss;
            ss << "QNumber::QNumber(" << n << ", " << d << ", " << s << ") : d is 0";
            throw std::runtime_error(ss.str());
        }
    }
    Float to_float() override { 
        if((this->_flags | Flags::Infinity) != 0){
            return INFINITY;
        }
        return ((Float)this->_d) / this->_n;
    }
    Integer to_integer() override { return this->_n / this->_d; }
    bool is_zero() { return this->_d == 0; }

    void force_gcd(){
        auto den = greatest_common_denominator(this->_d, this->_n);
        this->_d /= den;
        this->_n /= den;
    }

    friend std::ostream& operator<<(std::ostream& os, const QNumber& n);

    friend bool operator<(const QNumber& a, const QNumber& b);
    operator Float() const {
        return make_number(this->_s) * (Float(this->_d) / this->_d);
    };

    friend QNumber operator-(const QNumber& a);

    friend QNumber operator+(const QNumber& a, const QNumber& b);
    friend QNumber operator-(const QNumber& a, const QNumber& b);
    friend QNumber operator*(const QNumber& a, const QNumber& b);
    friend QNumber operator/(const QNumber& a, const QNumber& b);
};

inline std::ostream& operator<<(std::ostream& os, const QNumber& n){
    os << n._s << n._n << " / " << n._d;
    return os;
}

inline bool operator<(const QNumber& a, const QNumber& b){
    return a._n * b._d < b._n * a._d;
}
inline QNumber operator-(const QNumber& a){
    auto c = a;
    c._s = !a._s;
    return c;
}

inline QNumber operator+(const QNumber& a, const QNumber& b){
    QNumber out = {};
    if(a._s == b._s){
        out._n = a._n * b._d + b._n * a._d;
        out._d = b._d * a._d;
        out._s = a._s;
    }
    else{
        auto max = std::max(a, b);
        auto min = std::min(a, b);
        out._s = max._s;
        out._n = max._n * min._d - min._n * max._d;
        out._d = min._d * max._d;
    }
    out.force_gcd();

    return out;
}

inline QNumber operator-(const QNumber& a, const QNumber& b){
    return a + -b;
}

inline QNumber operator*(const QNumber& a, const QNumber& b){
    QNumber out = {
        a._n * b._n,
        a._d * b._d,
        a._s * b._s
    };
    out.force_gcd();

    return out;
}

inline QNumber operator/(const QNumber& a, const QNumber& b){
    QNumber out = {
        a._n * b._d,
        a._d * b._n,
        a._s * b._s
    };

    if(out._d != 0)
        out.force_gcd();
    if(a._n == 0 || b._n == 0){
        out._flags = (QNumber::Flags)(out._flags | (int)QNumber::Flags::Infinity);
    }

    return out;
}

}

#endif
