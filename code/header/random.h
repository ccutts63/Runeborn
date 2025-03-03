#pragma once

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

inline short int new_rnd_num(int from, int upTo = -1) {
    if (upTo == -1) {
        // If only one argument is provided, treat 'from' as 'upTo' and set 'from' to 0
        upTo = from;
        from = 0;
    }

    // Ensure 'from' is less than or equal to 'upTo'
    if (from > upTo) {
        std::swap(from, upTo);  // Swap if 'from' is greater than 'upTo'
    }


    // Generate a random number between 'from' and 'upTo' (inclusive)
    return rand() % (upTo - from + 1) + from;
}

inline short int BiasedRandom(int upTo, float targetPercentage) {
    float probability = targetPercentage / 100.0f;  // Convert percentage to decimal

    // Ensure valid probability range
    if (probability <= 0.0f) return 0;
    if (probability >= 1.0f) return upTo;

    // Calculate exponent dynamically so the highest value occurs at the target probability
    float exponent = log(1.0f - probability) / log(0.5);

    // Generate biased random float
    float randFloat = static_cast<float>(rand()) / RAND_MAX;
    randFloat = pow(randFloat, exponent);

    // Scale to range 0 to upTo (rounding ensures full range is used)
    return static_cast<short int>(round(randFloat * upTo));
}
