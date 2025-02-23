#ifndef MovingAverages_h
#define MovingAverages_h

#include <deque>

// Calculate Simple Moving Average
float calculateSMA(const std::deque<float>& prices);

// Calculate Exponential Moving Average
float calculateEMA(float currentPrice, float prevEMA, int period);

#endif /* MovingAverages_h */ 