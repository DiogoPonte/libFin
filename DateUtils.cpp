#include "DateUtils.h"
#include <sstream>

std::string convertDateFormat(const std::string& date) {
    if (date == "Date") return date; // Handle header row
    
    std::stringstream ss(date);
    std::string month, day, year;
    
    getline(ss, month, '/');
    getline(ss, day, '/');
    getline(ss, year);
    
    return day + "/" + month + "/" + year;
}

bool compareDates(const std::string& date1, const std::string& date2) {
    std::stringstream ss1(date1), ss2(date2);
    std::string day1, month1, year1, day2, month2, year2;
    
    getline(ss1, day1, '/');
    getline(ss1, month1, '/');
    getline(ss1, year1);
    
    getline(ss2, day2, '/');
    getline(ss2, month2, '/');
    getline(ss2, year2);
    
    // Compare years first
    if (year1 != year2) return year1 < year2;
    // Then months
    if (month1 != month2) return stoi(month1) < stoi(month2);
    // Finally days
    return stoi(day1) < stoi(day2);
}

float stringToPrice(const std::string& price) {
    return std::stof(price);
} 