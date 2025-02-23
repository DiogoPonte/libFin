#ifndef StockData_h
#define StockData_h

#include <string>

struct StockData {
    std::string date;
    std::string close;
    std::string volume;
    std::string open;
    std::string high;
    std::string low;
    float closePrice;  // Added for numeric calculations
    float sma;         // To store SMA value
    float ema;         // To store EMA value
    
    // Bollinger Bands
    float upperBand;
    float lowerBand;
    
    // Stochastic RSI
    float rsi;         // Regular RSI
    float stochRSI;    // Stochastic RSI
    float stochRSI_K;  // Stochastic RSI %K line
    float stochRSI_D;  // Stochastic RSI %D line
};

#endif /* StockData_h */ 