#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cmath>

#include "rational.hpp"

using namespace rational;

TEST_CASE("Test the fusc function") {
    CHECK(fusc(0) == 0);
    CHECK(fusc(1) == 1);
    CHECK(fusc(1081) == 53);
    CHECK(fusc(91) == 19);
    CHECK(fusc(19573419) == 103682);
    CHECK(fusc(2) == 1);
    CHECK(fusc(pow(2, 53)) == 1);
    CHECK(fusc(pow(2, 53) - 1) == 53);
    CHECK(fusc(4094) == 1);
    CHECK(fusc(4095) == 12);
    CHECK(fusc(14) == 3);
    CHECK(fusc(15) == 4);
    CHECK(fusc(62) == 5);
    CHECK(fusc(63) == 6);
    
}

TEST_CASE("Test inverse fusc") {
    CHECK(inverse_fusc(0, 1) == 0);
    CHECK(inverse_fusc(1, 1) == 1);
    CHECK(inverse_fusc(3, 1) == 0b111);
    CHECK(inverse_fusc(53, 37) == 1081);
    CHECK(inverse_fusc(37, 53) == 1990);
    CHECK(inverse_fusc(2, 2) == 1);
    CHECK(inverse_fusc(40, 48) == 62);
    CHECK(inverse_fusc(1, 12) == 4094);
    CHECK(inverse_fusc(3, 4) == 14);   
    CHECK(inverse_fusc(5, 6) == 62); 
}

TEST_CASE("Test rational addition") {
    CHECK(Rational(1, 1) + Rational(2, 1) == Rational(3, 1));
    CHECK(Rational(3, 2) + Rational(2, 3) == Rational(13, 6));
    CHECK(Rational(32, 122) + Rational(123, 3543) == Rational(21397, 72041));
    CHECK(Rational(1, 12) + Rational(3, 4) == Rational(5, 6));
}