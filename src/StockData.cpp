#ifndef StockData_cpp
#define StockData_cpp

// Standard includes.
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

#include "StockData.hpp"

StockData::StockData(const std::string& filename, float frequency, float riskFreeRate) 
    : frequency(frequency), riskFreeRate(riskFreeRate) 
{
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line); // skip the header
    
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // Get all values in the row
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Store values in vectors
        date.push_back(row[0]);
        open.push_back(stod(row[1]));
        high.push_back(stod(row[2]));
        low.push_back(stod(row[3]));
        close.push_back(stod(row[4]));
        adjClose.push_back(stod(row[5]));
        volume.push_back(stod(row[6]));

        // Compute period return and excess period return, with assumed risk-free rate
        if (date.size() > 1) {
            periodReturn.push_back((adjClose.back() - adjClose[adjClose.size()-2]) / adjClose[adjClose.size()-2]);
            excessPeriodReturn.push_back(periodReturn.back() - (riskFreeRate / (252 / frequency)));
        } else {
            periodReturn.push_back(0.0);
            excessPeriodReturn.push_back(0.0);
        }
    }
}

void StockData::printData() const {
    for (int i = 0; i < date.size(); i++) {
        std::cout << date[i] << " " << open[i] << " " << high[i] << " " << low[i] << " " << close[i] << " " << adjClose[i] << " " << volume[i] << " " << periodReturn[i] << " " << excessPeriodReturn[i] << std::endl;
    }
}

double StockData::computeSharpe() {
    double sum = std::accumulate(std::begin(excessPeriodReturn), std::end(excessPeriodReturn), 0.0);
    double m =  sum / excessPeriodReturn.size();
    double stdev = 0.0;
    std::for_each(std::begin(excessPeriodReturn), std::end(excessPeriodReturn), [&](const double d) {
        stdev += (d - m) * (d - m);
    });
    stdev = sqrt(stdev / excessPeriodReturn.size());
    return sqrt(252 / frequency) * (m / stdev);
}

#endif