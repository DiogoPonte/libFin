#ifndef BollingerBands_h
#define BollingerBands_h

#include <vector>
#include <deque>

// Calculate standard deviation for Bollinger Bands
float calculateStandardDeviation(const std::deque<float>& prices, float sma);

// Calculate Bollinger Bands (returns pair of upper and lower bands)
std::pair<float, float> calculateBollingerBands(float sma, float standardDeviation, float multiplier = 2.0f);

#endif /* BollingerBands_h */ 