#ifndef StockData_hpp
#define StockData_hpp

// Standard includes.
#include <vector>
#include <string>

class StockData {
    private: 
        // Data from file
        std::vector<std::string> timestamp;
        std::vector<double> open;
        std::vector<double> high;
        std::vector<double> low;
        std::vector<double> close;
        std::vector<double> volume;

        // Data computed from file data
        std::vector<double> periodReturn;
        std::vector<double> excessPeriodReturn; 

        // Parameters
        float frequency;
        float nt; // periods in a trading year for the given frequency
        float riskFreeRate; // annualized risk-free rate

    public:
        /**
         * Constructor for StockData class.
         * 
         * Assumes that the data is in a csv file with the following columns:
         * 1. timestamp
         * 2. open
         * 3. high
         * 4. low
         * 5. close (assumed to be adjusted close)
         * 6. volume
         * 
         * @param filename The name of the file to read data from.
         * @param nt The number of trading periods in a year for the given frequency.
         * @param riskFreeRate The annualized risk-free rate.
         */
        StockData(const std::string& filename, float nt, float riskFreeRate);

        /**
         * Destructor for StockData class.
         */
        ~StockData() = default;

        // Getter functions
        std::vector<double> getExcessPeriodReturn();
        double getExcessPeriodReturn(int time);
        double getOpen(int time);
        double getClose(int time);
        int getNumberOfEntries();

        // Print function
        void printData() const;
};

#endif