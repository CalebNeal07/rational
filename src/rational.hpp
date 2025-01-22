#include <cstdint>
#include <iostream>

namespace rational {

uint64_t fusc(uint64_t n);
uint64_t inverse_fusc(uint64_t p, uint64_t q);

struct Rational {
    uint64_t val;
    
    Rational(uint64_t p, uint64_t q);

    // // Utility Functions
    // rational& reciprocal(); 

    // Output Stream Overload
    friend std::ostream& operator<<(std::ostream&, const Rational&);

    // Binary Arithmetic Operators
    Rational operator+(Rational const&);
    Rational operator-(Rational const&);
    Rational operator*(Rational const&);
    Rational operator/(Rational const&);

    // // Unary Operators
    // rational& operator++();
    // rational& operator--();

    // // Assignment Operators
    // rational& operator+=(rational const& rhs);
    // rational& operator-=(rational const& rhs);
    // rational& operator*=(rational const& rhs);
    // rational& operator/=(rational const& rhs);
};

bool operator==(Rational const&, Rational const&);

} // namespace rational