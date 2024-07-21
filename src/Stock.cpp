// Standard includes.
#include <vector>
#include <functional>

#include "Stock.hpp"

double Stock::buyOpen(
    int period,
    double amount,
    std::function<double(int, double)> commission
) {
    double stockPrice = data.getOpen(period);
    double shares = amount / stockPrice;
    double commissionCost = commission(period, amount);
    return - (amount + commissionCost);
}

double Stock::buyClose(
    int period,
    double amount,
    std::function<double(int, double)> commission
) {
    double stockPrice = data.getClose(period);
    double shares = amount / stockPrice;
    double commissionCost = commission(period, amount);
    return - (amount + commissionCost);
}

double Stock::sellOpen(
    int period,
    double amount,
    std::function<double(int, double)> commission
) {
    double stockPrice = data.getOpen(period);
    double shares = amount / stockPrice;
    double commissionCost = commission(period, amount);
    return amount - commissionCost;
}

double Stock::sellClose(
    int period,
    double amount,
    std::function<double(int, double)> commission
) {
    double stockPrice = data.getClose(period);
    double shares = amount / stockPrice;
    double commissionCost = commission(period, amount);
    return amount - commissionCost;
}