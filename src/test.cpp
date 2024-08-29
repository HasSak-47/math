#include <iostream>
#include <math/math.hpp>
#include <math/number.hpp>
#include <math/test.hpp>
#include <ostream>

using namespace Ly::Math;

bool test_numbers(bool force_log){
    bool any_err = false;
    for(int sign_code = 0; sign_code < 4; ++sign_code){
        for(Integer dn_a = 0; dn_a < 100; ++dn_a){
            for(Integer dn_b = 0; dn_b < 100; ++dn_b){
                Integer na = dn_a % 10;
                Integer da = 1 + (dn_a % 10);
                Sign sa = (sign_code & 0b01) ? Sign::Positive : Sign::Negative;

                Integer nb = dn_b % 10;
                Integer db = 1 + (dn_b % 10);
                Sign sb = (sign_code & 0b10) ? Sign::Positive : Sign::Negative;

                QNumber qa = QNumber(na, da, sa);
                QNumber qb = QNumber(nb, db, sb);

                Float fa = make_number(sa) * ((Float)na / da);
                Float fb = make_number(sb) * ((Float)nb / db);

                QNumber aq = qa + qb;
                QNumber sq = qa - qb;
                QNumber mq = qa * qb;
                QNumber dq = fb != 0 ? qa / qb : QNumber();

                Float af = fa + fb;
                Float sf = fa - fb;
                Float mf = fa * fb;
                Float df = fb != 0 ? fa / fb : 0.;

                Float ar = aq.to_float() / af;
                Float sr = sq.to_float() / sf;
                Float mr = mq.to_float() / mf;
                Float dr = dq.to_float() / df;

                bool ae = std::abs(ar) < 0.01;
                bool se = std::abs(sr) < 0.01;
                bool me = std::abs(mr) < 0.01;
                bool de = std::abs(dr) < 0.01;

                bool error = ae || se || me || de;
                any_err = any_err || error;
                if(error || force_log){
                    std::cout << qa << " : " << qb << " <=> " << fa << " : " << fb <<std::endl;
                }
                if(ae || force_log) { std::cout << "\t add: " << aq << " (" << (Float)aq << ")" << " != " << af << std::endl; }
                if(se || force_log) { std::cout << "\t sub: " << sq << " (" << (Float)sq << ")" << " != " << sf << std::endl; }
                if(me || force_log) { std::cout << "\t mul: " << mq << " (" << (Float)mq << ")" << " != " << mf << std::endl; }
                if(de || force_log) { std::cout << "\t div: " << dq << " (" << (Float)dq << ")" << " != " << df << std::endl; }
            }
        }
    }

    return any_err;
}
