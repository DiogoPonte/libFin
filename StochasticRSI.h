#ifndef StochasticRSI_h
#define StochasticRSI_h

#include <deque>

// Structure to hold price changes for RSI calculation
struct PriceChange {
    float gain;
    float loss;
};

// Calculate Regular RSI
float calculateRSI(const std::deque<float>& prices, int period = 14);

// Calculate Raw Stochastic RSI value
float calculateRawStochRSI(const std::deque<float>& rsiValues, int period = 14);

// Calculate Stochastic RSI %K line (usually smoothed)
float calculateStochRSI_K(const std::deque<float>& rawStochRSI, int smoothK = 3);

// Calculate Stochastic RSI %D line (usually smoothed)
float calculateStochRSI_D(const std::deque<float>& stochRSI_K, int smoothD = 3);

#endif /* StochasticRSI_h */ 