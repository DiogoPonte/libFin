#ifndef DateUtils_h
#define DateUtils_h

#include <string>

// Helper function to convert date from mm/dd/yyyy to dd/mm/yyyy
std::string convertDateFormat(const std::string& date);

// Helper function to compare dates in dd/mm/yyyy format
bool compareDates(const std::string& date1, const std::string& date2);

// Helper function to convert string price to float
float stringToPrice(const std::string& price);

#endif /* DateUtils_h */ 