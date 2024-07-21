#ifndef Strategy_hpp
#define Strategy_hpp

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

#endif