#ifndef __random_h_
#define __random_h_

# include "../types.h"
# include "primes.h"
# include <algorithm> 
# include <iostream> 
# include <cmath>
# include <random>

static constexpr double DoubleOneMinusEpsilon = 0x1.fffffffffffffp-1;
static constexpr float FloatOneMinusEpsilon = 0x1.fffffep-1;

static constexpr float OneMinusEpsilon = FloatOneMinusEpsilon;


Vec3f Get2D() ;

float SampleDimension(int dimension);
Vec3f SampleUniformSphere(Vec3f w);
Vec3f sampleRoughReflection(Vec3f& V, Vec3f& N, 
                               float roughness, std::mt19937& rng);
Vec3f RandomUnitVector(std::mt19937& rng);
float RandomFloat01(std::mt19937& rng);

Vec3f jitter(Vec3f d, float phi, float sina, float cosa);
float erand48 (std::mt19937& rng, unsigned short xseed[3] = nullptr);

inline float RadicalInverse(int baseIndex, unsigned long long a) {
    unsigned int base = Primes[baseIndex];
    // We have to stop once reversedDigits is >= limit since otherwise the
    // next digit of |a| may cause reversedDigits to overflow.
    unsigned long long limit = ~0ull / base - base;
    
    float invBase = (float)1 / (float)base, invBaseM = 1;
    unsigned long long reversedDigits = 0;
    while (a && reversedDigits < limit) {
        // Extract least significant digit from _a_ and update _reversedDigits_
        unsigned long long next = a / base;
        unsigned long long digit = a - next * base;
        reversedDigits = reversedDigits * base + digit;
        invBaseM *= invBase;
        a = next;
    }
    return std::min(reversedDigits * invBaseM, OneMinusEpsilon);
}

#endif