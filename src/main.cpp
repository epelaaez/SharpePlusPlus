// Standard includes.
#include <iostream>

// Header includes.
#include "StockData.hpp"
#include "Strategy.hpp"

class DummyStrategy : public Strategy {
    using Strategy::Strategy;

    public:
        StockData stockData = StockData("data/IGE.csv", 1.0);

        double getPeriodExcessReturn(int time) override {
            return stockData.getExcessPeriodReturn(time);
        }
};

int main(int argc, char *argv[]) {
    DummyStrategy strat = DummyStrategy(1.0);
    std::cout << "Number of entries: " << strat.stockData.getNumberOfEntries() << std::endl;
    std::cout << "Sharpe ratio: " << strat.computeSharpe(0, 3137) << std::endl;
    return 0;
}