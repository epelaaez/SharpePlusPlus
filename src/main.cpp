#include <iostream>
#include "StockData.hpp"

int main(int argc, char *argv[]) {
    StockData IGE(argv[1], 1.0);
    std::cout << "Sharpe ratio: " << IGE.computeSharpe() << std::endl;
    return 0;
}