// Standard includes.
#include <iostream>

// Header includes.
#include "Stock.hpp"
#include "Strategy.hpp"

class HoldStrategy : public Strategy {
    using Strategy::Strategy;

    public:
        Stock stock = Stock("data/IGE.csv", nt);

        double getPeriodExcessReturn(int time) override {
            return stock.data.getExcessPeriodReturn(time);
        }
};

int main(int argc, char *argv[]) {
    HoldStrategy strat = HoldStrategy(252);

    std::cout << "IGE hold strategy" << std::endl;
    int numberOfEntries = strat.stock.data.getNumberOfEntries();
    std::cout << "Number of entries: " << numberOfEntries << std::endl;
    std::cout << "Sharpe ratio: " << strat.computeSharpe(0, numberOfEntries) << std::endl;
    std::cout << std::endl;

    // To compute N_T we note that we have 16 hours of data per day, 
    // so we have 16 * 252 = 4032 trading periods in a year.
    PairTrading pairStrat = PairTrading(
        4032, 
        Stock("data/NVDA.csv", 4032), 
        Stock("data/TSM.csv", 4032),
        0.01,
        0.003, // still have to refine this numbers, use stds
        0.02,
        10000.,
        50000.,
        0.04
    );
    std::cout << "NVDA-TSM pair trading strategy" << std::endl;
    numberOfEntries = Stock("data/NVDA.csv", 4032).data.getNumberOfEntries();
    std::cout << "Number of entries: " << numberOfEntries << std::endl;
    std::cout << "Sharpe ratio: " << pairStrat.computeSharpe(0, numberOfEntries) << std::endl;
    std::cout << "Final total: " << pairStrat.getTotal() << std::endl;

    return 0;
}