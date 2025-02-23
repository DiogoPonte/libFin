#include "StochasticRSI.h"
#include <algorithm>
#include <numeric>

float calculateRSI(const std::deque<float>& prices, int period) {
    if (prices.size() <= 1) return 0.0f;
    
    // Calculate price changes
    std::deque<PriceChange> changes;
    for (size_t i = 1; i < prices.size(); ++i) {
        float change = prices[i] - prices[i-1];
        changes.push_back({
            std::max(change, 0.0f),  // gain
            std::max(-change, 0.0f)  // loss
        });
    }
    
    // Calculate initial averages
    float avgGain = 0.0f;
    float avgLoss = 0.0f;
    
    // Use first 'period' elements for initial averages
    for (int i = 0; i < period && i < changes.size(); ++i) {
        avgGain += changes[i].gain;
        avgLoss += changes[i].loss;
    }
    
    avgGain /= period;
    avgLoss /= period;
    
    // Calculate RSI
    if (avgLoss == 0.0f) return 100.0f;
    
    float rs = avgGain / avgLoss;
    return 100.0f - (100.0f / (1.0f + rs));
}

float calculateRawStochRSI(const std::deque<float>& rsiValues, int period) {
    if (rsiValues.size() < period) return 0.0f;
    
    // Get min and max RSI values in the period
    float minRSI = *std::min_element(rsiValues.begin(), rsiValues.end());
    float maxRSI = *std::max_element(rsiValues.begin(), rsiValues.end());
    
    // Calculate Stochastic RSI
    if (maxRSI == minRSI) return 0.0f;
    
    float currentRSI = rsiValues.back();
    return (currentRSI - minRSI) / (maxRSI - minRSI);
}

float calculateStochRSI_K(const std::deque<float>& rawStochRSI, int smoothK) {
    if (rawStochRSI.size() < smoothK) return 0.0f;
    
    // Calculate simple moving average for smoothK period
    float sum = std::accumulate(rawStochRSI.end() - smoothK, rawStochRSI.end(), 0.0f);
    return sum / smoothK;
}

float calculateStochRSI_D(const std::deque<float>& stochRSI_K, int smoothD) {
    if (stochRSI_K.size() < smoothD) return 0.0f;
    
    // Calculate simple moving average for smoothD period
    float sum = std::accumulate(stochRSI_K.end() - smoothD, stochRSI_K.end(), 0.0f);
    return sum / smoothD;
} 