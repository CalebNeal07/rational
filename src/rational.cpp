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

uint64_t inverse_fusc(uint64_t p, uint64_t q) {
    int d = std::gcd(p, q);
    p /= d;
    q /= d;

    if (q == 1) {
        return ~(~0ULL << p);
    }

    if (p == 1) {
        return ~(~0ULL << q) << 1;
    }

    uint64_t val = ~0ULL;

    bool signal = p < q;

    if (signal) {
        val = ~val;
        std::swap(p, q);
    }

    while (q) {
        int shift = p / q;
        val = signal ? (~val) >> shift : ~(val >> shift);
        p -= shift * q;
        std::swap(p, q);
    }
    
    val = ~val;
    val |= 1ULL << 63;
    val >>= signal ? __builtin_ctzll(~val) : __builtin_ctzll(val);

    return val;
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
    std::cout << "val: " << val << std::endl;
    uint64_t n_0 = rational::fusc(this->val);
    uint64_t n_1 = rational::fusc(this->val + 1);
    uint64_t m_0 = rational::fusc(rhs.val);
    uint64_t m_1 = rational::fusc(rhs.val + 1);
    uint64_t numerator = (n_0 * m_1) + (m_0 * n_1);
    uint64_t denominator = n_1 * m_1;
    return Rational(numerator, denominator);
}

// Rational::operator-(Rational) {
//     uint64_t n_0 = rational::fusc(this->val);
//     uint64_t n_1 = rational::fusc(this->val + 1);
//     uint64_t m_0 = rational::fusc(rhs->val);
//     uint64_t m_1 = rational::fusc(rhs->val + 1);
//     return rational::inverse_fusc((n_0 * m_1) - (m_0 * n_1), n_1 * m_1);
// }

// Rational::operator*(Rational const& rhs) {
//     uint64_t n_0 = rational::fusc(this->val);
//     uint64_t n_1 = rational::fusc(this->val + 1);
//     uint64_t m_0 = rational::fusc(rhs->val);
//     uint64_t m_1 = rational::fusc(rhs->val + 1);
//     return rational::inverse_fusc(n_0 * m_0, n_1 * m_1);
// }

// Rational::operator/(Rational const^ rhs) {
//     uint64_t n_0 = rational::fusc(this->val);
//     uint64_t n_1 = rational::fusc(this->val + 1);
//     uint64_t m_0 = rational::fusc(rhs->val);
//     uint64_t m_1 = rational::fusc(rhs->val + 1);
//     return rational::inverse_fusc(n_0 * m_1, n_1 * m_0);
// }

}