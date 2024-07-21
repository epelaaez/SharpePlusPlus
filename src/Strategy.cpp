// Standard includes.
#include <vector>
#include <numeric>

#include "Strategy.hpp"

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