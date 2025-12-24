#include "random.h"
#include "ray.h"
#include "math.h"

std::uniform_real_distribution<double> distribution;

Vec3f SampleUniformSphere(Vec3f w) {
    float z = 1.f - 2.f * w.x;
    float r = SafeSqrt(1 - z * z);
    float phi = 2.f * PI * w.y;
    return Vec3f(r * std::cos(phi), r * std::sin(phi), z);
}

int dimension = 0;

Vec3f Get2D() {
    if (dimension + 1 >= PrimeTableSize)
        dimension = 2;
    int dim = dimension;
    dimension += 2;
    return Vec3f(SampleDimension(dim), SampleDimension(dim + 1), 0.f);
}

float SampleDimension(int dimension) {
    // if (randomize == RandomizeStrategy::None)
        return RadicalInverse(dimension, 1000000000000);
    
    // else if (randomize == RandomizeStrategy::PermuteDigits)
    //     return ScrambledRadicalInverse(dimension, haltonIndex,
    //                                     (*digitPermutations)[dimension]);
    // else {
    //     DCHECK_EQ(randomize, RandomizeStrategy::Owen);
    //     return OwenScrambledRadicalInverse(dimension, haltonIndex,
    //                                         MixBits(1 + (dimension << 4)));
    // }
}

float seed = 0.;

float RandomFloat01(std::mt19937& rng) {
    std::uniform_real_distribution<float> dist(0.0f, 1.f);
    return dist(rng);
}

Vec3f RandomUnitVector(std::mt19937& rng)
{
    std::uniform_real_distribution<float> dist(0.0f, 1.f);
    float xi1 = dist(rng);
    float xi2 = dist(rng);

    float z = xi1 * 2.0f - 1.0f;
    float a = xi2 * PI2;
    float r = sqrt(1.0f - z * z);
    float x = r * cos(a);
    float y = r * sin(a);
    return Vec3f(x, y, z);
}

Vec3f sampleRoughReflection(Vec3f& V, Vec3f& N, 
                               float roughness, std::mt19937& rng) {
    roughness = std::max(0.001f, roughness);
    float alpha = roughness * roughness;
    
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float xi1 = dist(rng);
    float xi2 = dist(rng);
    
    // Выборка GGX
    float phi = 2.0f * PI * xi1;
    float cosTheta = sqrt((1.0f - xi2) / (1.0f + (alpha*alpha - 1.0f) * xi2));
    float sinTheta =  sqrt(std::max(0.0f, 1.0f - cosTheta*cosTheta));
    
    // Локальная микронормаль
    Vec3f H_local(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
    
    // Базис
    Vec3f T, B;
    if (abs(N.x) > abs(N.y)) {
        T = Vec3f(N.z, 0.0f, -N.x).normalize();
    } else {
        T = Vec3f(0.0f, -N.z, N.y).normalize();
    }

    // Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    // if (std::abs(dot(N, up)) > 0.999f) {
    //     up = Vec3f(1.0f, 0.0f, 0.0f);
    // }
    // T = (up* N).normalize();

    B = cross(N, T).normalize();
    
    // В мировые координаты
    Vec3f H = T * H_local.x + B * H_local.y + N * H_local.z;
    H = H.normalize();
    
    // Отражение
    Vec3f L = reflect(V, H);
    L = L.normalize();
    
    // Корректировка направления
    // if (dot(L, N) < 0.0f) {
    //     L = reflect(L, N);
    // }
    
    return L;
}

float erand48 (std::mt19937& rng, unsigned short *xseed) {
    if (xseed) {
        // Обновляем генератор, если передан новый seed
        uint64_t seed64 = (static_cast<uint64_t>(xseed[2]) << 32) |
                            (static_cast<uint64_t>(xseed[1]) << 16) |
                            static_cast<uint64_t>(xseed[0]);
        rng.seed(seed64);
    }
    return distribution(rng);
}

Vec3f jitter(Vec3f d, float phi, float sina, float cosa) {
	Vec3f w = d.normalize(), u = cross(Vec3f(w.y, w.z, w.x), w).normalize(), v = cross(w, u);
	return (u*cos(phi) + v*sin(phi)) * sina + w * cosa;
}

