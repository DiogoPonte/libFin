#include "MovingAverages.h"

float calculateSMA(const std::deque<float>& prices) {
    if (prices.empty()) return 0.0f;
    float sum = 0.0f;
    for (float price : prices) {
        sum += price;
    }
    return sum / prices.size();
}

float calculateEMA(float currentPrice, float prevEMA, int period) {
    float multiplier = 2.0f / (period + 1);
    return (currentPrice - prevEMA) * multiplier + prevEMA;
} 