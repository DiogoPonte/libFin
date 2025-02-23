#include "BollingerBands.h"
#include <cmath>

float calculateStandardDeviation(const std::deque<float>& prices, float sma) {
    if (prices.empty()) return 0.0f;
    
    float sumSquaredDiff = 0.0f;
    for (float price : prices) {
        float diff = price - sma;
        sumSquaredDiff += diff * diff;
    }
    
    return std::sqrt(sumSquaredDiff / prices.size());
}

std::pair<float, float> calculateBollingerBands(float sma, float standardDeviation, float multiplier) {
    float upperBand = sma + (standardDeviation * multiplier);
    float lowerBand = sma - (standardDeviation * multiplier);
    return std::make_pair(upperBand, lowerBand);
} 