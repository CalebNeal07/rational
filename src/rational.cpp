#include "rational.hpp"

#include <utility>
#include <numeric>
#include <vector>

namespace rational {

char *uint64_to_bin(uint64_t num) {
    char *str = (char*) malloc(65); // 64 bits + null terminator
    if (str == NULL) {
        return NULL; // Memory allocation failed
    }
    
    for (int i = 0; i < 64; i++) {
        // Calculate the bit position from MSB to LSB
        uint64_t bit_mask = (uint64_t)1 << (63 - i);
        str[i] = (num & bit_mask) ? '1' : '0';
    }
    str[64] = '\0'; // Null-terminate the string
    
    return str;
}

uint64_t fusc(uint64_t n) {
    int lz = __builtin_clzll(n);
    uint64_t mask = ~0 >> lz;
    mask <<= lz;
    uint64_t val = n;
    
    if (__builtin_ctzll(val) == 1) {
        val = ~(val | 1ULL);
    }

    val = ~(~n << lz); 
    
    uint64_t p = 1, q = 0; 

    //std::cout << " n \t p \t q \t term" << std::endl;
    while (mask) {
        val = val ^ mask;
        int term = __builtin_clzll(val);

        uint64_t temp = p;
        p = (term * p) + q;
        q = temp;

        val = ~(~val << term);
        mask = mask << term;
        //std::cout << val << "\t" << p << "\t" << q << "\t" << term << std::endl;
    }

    return n % 2 == 0 ? q : p;
}

// uint64_t fusc(uint64_t n) {

//     std::cout << "fusc(" << n << ")\n";
//     if (n <= 1) {
//         return n;
//     }

//     uint64_t val = n;
//     int lz = __builtin_clzll(val);
//     uint64_t mask = ~0 << lz;
//     if (__builtin_ctzll(val) == 1) {
//         val |= 1ULL;
//     }
//     val <<= lz;

//     uint64_t p = 1, q = 0;

//     while (val) {
//         int term = __builtin_clzll(val ^ mask);
//         p += term * q;
//         std::swap(p, q);
//         val <<= term;
//         mask <<= term;

//         std::cout << term << std::endl;

//         term = __builtin_clzll(~(val ^ mask));
//         p += term * q;
//         std::swap(p, q);
//         val <<= term;
//         mask <<= term;
        
//         std::cout << term << std::endl;
//     }

//     return p;
// }

/** INVERSE FUSC FUNCTION
 * Calculates the value of n given p and q which are fusc(n) and fusc(n+1) respectively.
 * Example Walkthrough
 */
uint64_t inverse_fusc(uint64_t p, uint64_t q) {
    uint64_t n = 0ULL;

    if (q == 1) {
        return ~(~n << p);
    }

    uint64_t mask = 0ULL;
    // std::cout << " p \t q \t shift \t n" << std::endl;
    // std::cout << ' ' << p << " \t" << q << " \t \t " << uint64_to_bin(n) << std::endl; 

    unsigned short shift = 0;
    bool flag = p < q;

    while (q) {
        shift = p / q;
        n = ~n;
        n >>= shift;
        mask = ~(~mask >> shift);
        std::swap(p, q);
        q -= shift * p;
        // std::cout << ' ' << p << "\t " << q << "\t " << shift << "\t " << uint64_to_bin(n) << std::endl;
    }

    if (flag) {
        n = ~n;
        n >>= __builtin_ctzll(mask);
        n &= ~0ULL << 1;
    } else {
        n |= 1ULL << 63;
        n >>= __builtin_ctzll(mask);
    }

    // std::cout << std::endl << "n = " << uint64_to_bin(n) << std::endl;

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
    // std::cout << "n: " << n_0 << "/" << n_1 << "\tm: " << m_0 << "/" << m_1 << std::endl;
    // std::cout << "denominator: " << denominator << "\tnumerator: " << numerator << std::endl;
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