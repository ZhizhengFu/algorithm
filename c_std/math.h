#include <stdint.h>

float Q_rsqrt(float number) {
    // Constants
    const float threehalfs = 1.5F;

    // Variables
    float x2 = number * 0.5F;
    float y = number;
    uint32_t i;

    // Convert float to int representation
    i = *(uint32_t*)&y;  // Treat float's bit pattern as an integer
    // Initial guess for Newton's method (magic number)
    i = 0x5f375a86 - (i >> 1);
    // Convert back to float
    y = *(float*)&i;

    // First iteration of Newton's method
    y = y * (threehalfs - (x2 * y * y));
    // Optional: Second iteration for more accuracy
    y = y * (threehalfs - (x2 * y * y));

    return y;
}
