#ifndef Stock_hpp
#define Stock_hpp

// Standard includes.
#include <vector>
#include <functional>

#include "StockData.hpp"

class Stock {
    public:
        // Constructor
        Stock(
            const std::string& filename,
            float nt,
            float riskFreeRate = 0.04
        ) : data(StockData(filename, nt, riskFreeRate)) {};

        // Destructor
        ~Stock() = default;

        StockData data;

        double buyOpen(int period, double amount, std::function<double(int, double)> commission);
        double buyClose(int period, double amount, std::function<double(int, double)> commission);
        double sellOpen(int period, double amount, std::function<double(int, double)> commission);
        double sellClose(int period, double amount, std::function<double(int, double)> commission);
};

#endif