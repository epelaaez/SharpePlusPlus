#ifndef Strategy_hpp
#define Strategy_hpp

#include "Stock.hpp"

class Strategy {
    public:
        /**
         * Constructor for Strategy class.
         * 
         * @param nt The number of trading periods in a year for the given frequency.
         */
        Strategy(float nt) : nt(nt) {};

        /**
         * Destructor for Strategy class.
         */
        ~Strategy() = default;

        virtual double getPeriodExcessReturn(int time) = 0;

        /**
         * Compute the Sharpe ratio for the implemented strategy.
         * 
         * @param start The starting period for the Sharpe ratio calculation.
         * @param end The ending period for the Sharpe ratio calculation.
         * @return The Sharpe ratio for the implemented strategy.
         */
        double computeSharpe(int start, int end);

    protected:
        // Parameters
        float nt;
};

class PairTrading : public Strategy {
    public:
        /**
         * Constructor for PairTrading class.
         * 
         * @param nt The number of trading periods in a year for the given frequency.
         * @param stockOne The first stock to trade.
         * @param stockTwo The second stock to trade.
         * @param targetOpenSpread The target spread at which to open the trade.
         * @param targetCloseSpread The target spread at which to close the trade.
         * @param stopLossSpread The spread at which to close trade at a loss.
         * @param amount The amount to trade, (in dollars).
         * @param total The starting amount of money.
         * @param riskFreeRate The annualized risk-free rate.
         */
        PairTrading(
            float nt, 
            Stock stockOne, 
            Stock stockTwo,
            float targetOpenSpread,
            float targetCloseSpread,
            float stopLossSpread,
            float amount,
            float total,
            float riskFreeRate
        ) : Strategy(nt), 
            stockOne(stockOne), 
            stockTwo(stockTwo), 
            targetOpenSpread(targetOpenSpread), 
            targetCloseSpread(targetCloseSpread), 
            stopLossSpread(stopLossSpread), 
            amount(amount), 
            total(total),
            riskFreeRate(riskFreeRate) 
        {};

        /**
         * Destructor for PairTrading class.
         */
        ~PairTrading() = default;

        double getPeriodExcessReturn(int time) override;

        double getTotal() {
            return total;
}

    private:
        Stock stockOne;
        Stock stockTwo;
        float targetOpenSpread;
        float targetCloseSpread;
        float stopLossSpread;
        float amount;
        float total;
        float riskFreeRate;

        bool inTrade;
        int tradeOpenTime;
        Stock* longStock = nullptr;
        Stock* shortStock = nullptr;
        float shortSharesAmount;
        float longSharesAmount;
        std::vector<double> tracker;
};

#endif