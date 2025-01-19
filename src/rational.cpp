#include "rational.hpp"

#include <utility>
#include <iostream>

uint64_t rational::fusc(uint64_t n) {
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

uint64_t rational::inverse_fusc(uint64_t p, uint64_t q) {
    if (q == 1) {
        return ~(~0ULL << p);
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

rational::Rational::Rational(uint64_t p, uint64_t q) {
    val = rational::inverse_fusc(p, q);
}