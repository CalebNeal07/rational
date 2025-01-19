#include <cstdint>

namespace rational {

uint64_t fusc(uint64_t n);
uint64_t inverse_fusc(uint64_t p, uint64_t q);

class Rational {
    uint64_t val;

public:
    
    Rational(uint64_t p, uint64_t q);

    // // Utility Functions
    // rational& reciprocal(); 

    // // Binary Arithmetic Operators
    // rational operator+(rational const& rhs);
    // rational operator-(rational const& rhs);
    // rational operator*(rational const& rhs);
    // rational operator/(rational const& rhs);
    // rational operator^(rational const& rhs);

    // // Unary Operators
    // rational& operator++();
    // rational& operator--();

    // // Assignment Operators
    // rational& operator+=(rational const& rhs);
    // rational& operator-=(rational const& rhs);
    // rational& operator*=(rational const& rhs);
    // rational& operator/=(rational const& rhs);
};

} // namespace rational