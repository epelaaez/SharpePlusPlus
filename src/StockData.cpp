// Standard includes.
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

#include "StockData.hpp"

StockData::StockData(const std::string& filename, float nt, float riskFreeRate) 
    : nt(nt), riskFreeRate(riskFreeRate) 
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
        timestamp.push_back(row[0]);
        open.push_back(stod(row[1]));
        high.push_back(stod(row[2]));
        low.push_back(stod(row[3]));
        close.push_back(stod(row[4]));
        volume.push_back(stod(row[5]));

        // Compute period return and excess period return, with assumed risk-free rate
        if (timestamp.size() > 1) {
            periodReturn.push_back((close.back() - close[close.size()-2]) / close[close.size()-2]);
            excessPeriodReturn.push_back(periodReturn.back() - (riskFreeRate / nt));
        } else {
            periodReturn.push_back(0.0);
            excessPeriodReturn.push_back(0.0);
        }
    }
}

void StockData::printData() const {
    for (int i = 0; i < timestamp.size(); i++) {
        std::cout << timestamp[i] << " " << open[i] << " " << high[i] << " " << low[i] << " " << close[i] << " " << close[i] << " " << volume[i] << " " << periodReturn[i] << " " << excessPeriodReturn[i] << std::endl;
    }
}

std::vector<double> StockData::getExcessPeriodReturn() {
    return excessPeriodReturn;
}

double StockData::getExcessPeriodReturn(int time) {
    if (time >= 0 && time < excessPeriodReturn.size()) {
        return excessPeriodReturn[time];
    } else {
        throw std::out_of_range("Time provided is out of range");
    }
}

double StockData::getClose(int time) {
    if (time >= 0 && time < close.size()) {
        return close[time];
    } else {
        throw std::out_of_range("Time provided is out of range");
    }
}

double StockData::getOpen(int time) {
    if (time >= 0 && time < open.size()) {
        return open[time];
    } else {
        throw std::out_of_range("Time provided is out of range");
    }
}

int StockData::getNumberOfEntries() {
    return timestamp.size();
}