#ifndef StockData_hpp
#define StockData_hpp

// Standard includes;
#include <vector>
#include <string>

class StockData {
    private: 
        // Data from file
        std::vector<std::string> date;
        std::vector<double> open;
        std::vector<double> high;
        std::vector<double> low;
        std::vector<double> close;
        std::vector<double> adjClose;
        std::vector<double> volume;

        // Data computed from file data
        std::vector<double> periodReturn;
        std::vector<double> excessPeriodReturn; 

        // Parameters
        float frequency; 
        float riskFreeRate; // annualized risk-free rate

    public:
        // Constructor
        StockData(const std::string& filename, float frequency, float riskFreeRate = 0.04);

        // Destructor
        ~StockData() = default;

        void printData() const;
        double computeSharpe();
};

#endif