#include "util.h"

double degreesToRadians(const double deg) {
    return deg * PI / 180.0;
}

// Returns random number in [0, 1)
double randomDouble() {
    static std::uniform_real_distribution<double> distribution{0.0, 1.0};
    static std::mt19937 generator;
    return distribution(generator);
}

// Returns random number in [min, max)
double randomDouble(const double min, const double max) {
    return min + (max-min) * randomDouble();
}

double randomDouble(const int min, const int max) {
    return min + (max-min) * randomDouble();
}

int randomInt(const int min, const int max) {
    return static_cast<int>(randomDouble(min, max + 1));
}

static unsigned long x=123456789, y=362436069, z=521288629;

double fastRandomDouble(void) {  //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return (double) z / ULONG_MAX;
}

double fastRandomDouble(const double min, const double max) {
    return min + (max-min) * fastRandomDouble();
}

float fastInvSqrt(float number) {
	static_assert(std::numeric_limits<float>::is_iec559); // (enable only on IEEE 754)

	float y = std::bit_cast<float>(
		0x5f3759df - (std::bit_cast<std::uint32_t>(number) >> 1)
    );
    y = y * (1.5f - (number * 0.5f * y * y));
    // y = y * (1.5f - (number * 0.5f * y * y));
	return y;
}