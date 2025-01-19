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
}

TEST_CASE("Test inverse fusc") {
    CHECK(inverse_fusc(0, 1) == 0);
    CHECK(inverse_fusc(1, 1) == 1);
    CHECK(inverse_fusc(53, 37) == 1081);
    CHECK(inverse_fusc(37, 53) == 1990);
}