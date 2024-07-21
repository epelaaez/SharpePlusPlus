// Standard includes.
#include <iostream>

// Header includes.
#include "Stock.hpp"
#include "Strategy.hpp"

class DummyStrategy : public Strategy {
    using Strategy::Strategy;

    public:
        Stock stock = Stock("data/IGE.csv", nt);

        double getPeriodExcessReturn(int time) override {
            return stock.data.getExcessPeriodReturn(time);
        }
};

int main(int argc, char *argv[]) {
    // To compute N_T we note that we have 16 hours of data per day, 
    // so we have 16 * 252 = 4032 trading periods in a year.
    DummyStrategy strat = DummyStrategy(252);

    int numberOfEntries = strat.stock.data.getNumberOfEntries();
    std::cout << "Number of entries: " << numberOfEntries << std::endl;
    std::cout << "Sharpe ratio: " << strat.computeSharpe(0, numberOfEntries) << std::endl;

    return 0;
}