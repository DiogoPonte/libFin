#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <iomanip>
#include "StockData.h"
#include "DateUtils.h"
#include "MovingAverages.h"
#include "BollingerBands.h"
#include "StochasticRSI.h"

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define WHITE   "\033[37m"

int main(int argc, const char * argv[]) {
    std::cout << "Opening file\n";
    
    std::ifstream file("/Users/diogoponte/Documents/Dev/C++/libFin/libFin/prices.csv");
    
    if (!file.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return 1;
    }
    
    std::vector<StockData> stockData;
    std::string line;
    bool firstLine = true;
    
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header row
        }
        
        // Remove all $ symbols from the line
        line.erase(std::remove(line.begin(), line.end(), '$'), line.end());
        std::stringstream ss(line);
        StockData row;
        
        getline(ss, row.date, ',');
        getline(ss, row.close, ',');
        getline(ss, row.volume, ',');
        getline(ss, row.open, ',');
        getline(ss, row.high, ',');
        getline(ss, row.low, ',');
        
        row.date = convertDateFormat(row.date);
        row.closePrice = stringToPrice(row.close);
        stockData.push_back(row);
    }
    
    file.close();
    
    // Sort the data by date
    std::sort(stockData.begin(), stockData.end(), 
              [](const StockData& a, const StockData& b) {
                  return compareDates(a.date, b.date);
              });
    
    // Parameters for technical indicators
    const int smaPeriod = 20;
    const int rsiPeriod = 14;
    const int stochPeriod = 14;
    const int smoothK = 3;
    const int smoothD = 3;
    
    std::deque<float> priceWindow;
    std::deque<float> rsiValues;
    std::deque<float> rawStochRSI;
    std::deque<float> stochRSI_K;
    float prevEMA = 0.0f;
    bool firstEMA = true;
    
    // Calculate indicators for each day
    for (size_t i = 0; i < stockData.size(); ++i) {
        // Update price window
        priceWindow.push_back(stockData[i].closePrice);
        if (priceWindow.size() > smaPeriod) {
            priceWindow.pop_front();
        }
        
        // Calculate SMA and Bollinger Bands
        if (priceWindow.size() == smaPeriod) {
            stockData[i].sma = calculateSMA(priceWindow);
            
            // Calculate Bollinger Bands
            float stdDev = calculateStandardDeviation(priceWindow, stockData[i].sma);
            auto bands = calculateBollingerBands(stockData[i].sma, stdDev);
            stockData[i].upperBand = bands.first;
            stockData[i].lowerBand = bands.second;
            
            // Calculate EMA
            if (firstEMA) {
                stockData[i].ema = stockData[i].sma;
                prevEMA = stockData[i].ema;
                firstEMA = false;
            } else {
                stockData[i].ema = calculateEMA(stockData[i].closePrice, prevEMA, smaPeriod);
                prevEMA = stockData[i].ema;
            }
        } else {
            stockData[i].sma = 0.0f;
            stockData[i].ema = 0.0f;
            stockData[i].upperBand = 0.0f;
            stockData[i].lowerBand = 0.0f;
        }
        
        // Calculate RSI
        if (i >= rsiPeriod) {
            std::deque<float> rsiWindow(priceWindow.end() - rsiPeriod, priceWindow.end());
            stockData[i].rsi = calculateRSI(rsiWindow, rsiPeriod);
            rsiValues.push_back(stockData[i].rsi);
            
            if (rsiValues.size() > stochPeriod) {
                rsiValues.pop_front();
            }
            
            // Calculate Stochastic RSI
            if (rsiValues.size() == stochPeriod) {
                float rawStoch = calculateRawStochRSI(rsiValues, stochPeriod);
                rawStochRSI.push_back(rawStoch);
                
                if (rawStochRSI.size() > smoothK) {
                    rawStochRSI.pop_front();
                }
                
                if (rawStochRSI.size() == smoothK) {
                    float k = calculateStochRSI_K(rawStochRSI, smoothK);
                    stochRSI_K.push_back(k);
                    stockData[i].stochRSI_K = k;
                    
                    if (stochRSI_K.size() > smoothD) {
                        stochRSI_K.pop_front();
                    }
                    
                    if (stochRSI_K.size() == smoothD) {
                        stockData[i].stochRSI_D = calculateStochRSI_D(stochRSI_K, smoothD);
                    }
                }
            }
        }
    }
    
    // Print the data with all indicators
    std::cout << std::setw(12) << "Date" 
              << std::setw(10) << "Close" 
              << std::setw(10) << "SMA-20"
              << std::setw(10) << "BB-Up"
              << std::setw(10) << "BB-Low"
              << std::setw(10) << "RSI"
              << std::setw(10) << "StochK"
              << std::setw(10) << "StochD" << std::endl;
    
    for (const auto& row : stockData) {
        std::cout << std::setw(12) << row.date 
                  << std::setw(10) << std::fixed << std::setprecision(2) << row.closePrice
                  << std::setw(10) << row.sma
                  << std::setw(10) << row.upperBand
                  << std::setw(10) << row.lowerBand;
        
        // Color the RSI value based on conditions
        if (row.rsi <= 20.0f and row.rsi != 0.0f) {
            std::cout << RED;
        } else if (row.rsi >= 80.0f) {
            std::cout << GREEN;
        } else {
            std::cout << WHITE;
        }
        std::cout << std::setw(10) << row.rsi << RESET
                  << std::setw(10) << row.stochRSI_K
                  << std::setw(10) << row.stochRSI_D << std::endl;
    }
    
    return 0;
}