// Standard includes.
#include <iostream>
#include <vector>
#include <numeric>

#include "Strategy.hpp"
#include "Stock.hpp"

double Strategy::computeSharpe(int start, int end) {
    // Using the following to implement the stdev calculation:
    // https://en.wikipedia.org/wiki/Standard_deviation#Rapid_calculation_methods
    double s0 = 0.0; double s1 = 0.0; double s2 = 0.0;

    for (int i = start; i < end; i++) {
        double excessReturn = getPeriodExcessReturn(i);
        s0 += 1; s1 += excessReturn; s2 += excessReturn * excessReturn;
    }
    double m = s1 / s0;
    double stdev = sqrt(s0 * s2 - s1 * s1) / s0;

    return sqrt(nt) * (m / stdev);
}

double fivePointComission(int time, double amount) {
    // make this more accurate
    return 0.005;
}

double PairTrading::getPeriodExcessReturn(int time) {
    if (
        !inTrade && 
        abs(stockOne.data.getClose(time) - stockTwo.data.getClose(time)) >= targetOpenSpread
    ) {
        inTrade = true;
        tradeOpenTime = time;

        // We long the stock with the lower price and short the one
        // with the highest price.
        if (stockOne.data.getClose(time) < stockTwo.data.getClose(time)) {
            longStock = &stockOne; shortStock = &stockTwo;
        } else {
            longStock = &stockTwo; shortStock = &stockOne;
        }

        // Record how many shares we get of each position.
        longSharesAmount = amount / longStock->data.getClose(time);
        shortSharesAmount = amount / shortStock->data.getClose(time);

        // Open the trade.
        total += longStock->buyClose(time, amount, fivePointComission);
        total += shortStock->sellClose(time, amount, fivePointComission);

        std::cout << "Opened trade at time: " << time << std::endl;
        std::cout << "Long stock: ";
        std::cout << longStock->buyClose(time, amount, fivePointComission) << std::endl;
        std::cout << "Short stock: ";
        std::cout << shortStock->sellClose(time, amount, fivePointComission) << std::endl;
        std::cout << "Total: " << total << std::endl;
        std::cout << std::endl;

        tracker.push_back(total);
    } else if (
        inTrade && 
        (abs(stockOne.data.getClose(time) - stockTwo.data.getClose(time)) <= targetCloseSpread ||
        abs(stockOne.data.getClose(time) - stockTwo.data.getClose(time)) >= stopLossSpread)
    ) {
        inTrade = false;

        // Close the trade.
        total += longStock->sellClose(time, longSharesAmount * longStock->data.getClose(time), fivePointComission);
        total += shortStock->buyClose(time, shortSharesAmount * shortStock->data.getClose(time), fivePointComission);
        tracker.push_back(total);

        std::cout << "Closed trade at time: " << time << std::endl;
        std::cout << "Long stock: ";
        std::cout << longStock->sellClose(time, longSharesAmount * longStock->data.getClose(time), fivePointComission) << std::endl;
        std::cout << "Short stock: ";
        std::cout << shortStock->buyClose(time, shortSharesAmount * shortStock->data.getClose(time), fivePointComission) << std::endl;
        std::cout << "Total: " << total << std::endl;
        std::cout << std::endl;

        // Return the excess return.
        return ((tracker.back() - tracker[tracker.size()-2]) / tracker[tracker.size()-2]) - (riskFreeRate / nt);
    } else {
        tracker.push_back(total);
    }
    return 0.0;
}