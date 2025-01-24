#include "rational.hpp"

#include <utility>
#include <numeric>

namespace rational {

uint64_t fusc(uint64_t n) {
    int lz = __builtin_clzll(n);
    uint64_t mask = ~0 >> lz;
    mask <<= lz;
    uint64_t val = ~(~n << lz);
    
    uint64_t p = 1, q = 0; 

    while (mask != 0) {
        val = val ^ mask;
        int term = __builtin_clzll(val);

        uint64_t temp = p;
        p = (term * p) + q;
        q = temp;

        val = ~(~val << term);
        mask = mask << term;
    }

    return n % 2 == 0 ? q : p;
}

/** INVERSE FUSC FUNCTION
 * Calculates the value of n given p and q which are fusc(n) and fusc(n+1) respectively.
 * Example Walkthrough
 */
uint64_t inverse_fusc(uint64_t p, uint64_t q) {
    uint64_t n = 0ULL;

    while (p != q) {
        n >>= p / q;
        n = ~n;
        std::cout << "n: " << n << std::endl;
        std::swap(p, q);
    }

    return n;
}

Rational::Rational(uint64_t p, uint64_t q) {
    val = rational::inverse_fusc(p, q);
}

std::ostream& operator<<(std::ostream& os, const Rational& frac) {
    os << fusc(frac.val) << "/" << fusc(frac.val + 1);
    return os;
}

bool operator==(Rational const& lhs, Rational const& rhs) {
    return lhs.val == rhs.val;
}

Rational Rational::operator+(Rational const& rhs) {
    uint64_t n_0 = rational::fusc(this->val);
    uint64_t n_1 = rational::fusc(this->val + 1);
    uint64_t m_0 = rational::fusc(rhs.val);
    uint64_t m_1 = rational::fusc(rhs.val + 1);
    uint64_t numerator = (n_0 * m_1) + (m_0 * n_1);
    uint64_t denominator = n_1 * m_1;
    return Rational(numerator, denominator);
}

Rational Rational::operator-(Rational const& rhs) {
    uint64_t n_0 = rational::fusc(this->val);
    uint64_t n_1 = rational::fusc(this->val + 1);
    uint64_t m_0 = rational::fusc(rhs.val);
    uint64_t m_1 = rational::fusc(rhs.val + 1);
    uint64_t numerator = (n_0 * m_1) - (m_0 * n_1);
    uint64_t denominator = n_1 * m_1;
    return Rational(numerator, denominator);
}

Rational Rational::operator*(Rational const& rhs) {
    uint64_t n_0 = rational::fusc(this->val);
    uint64_t n_1 = rational::fusc(this->val + 1);
    uint64_t m_0 = rational::fusc(rhs.val);
    uint64_t m_1 = rational::fusc(rhs.val + 1);
    return Rational(n_0 * m_0, n_1 * m_1);
}

Rational Rational::operator/(Rational const& rhs) {
    uint64_t n_0 = rational::fusc(this->val);
    uint64_t n_1 = rational::fusc(this->val + 1);
    uint64_t m_0 = rational::fusc(rhs.val);
    uint64_t m_1 = rational::fusc(rhs.val + 1);
    return Rational(n_0 * m_1, n_1 * m_0);
}

}