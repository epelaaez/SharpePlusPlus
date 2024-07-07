#ifndef Strategy_hpp
#define Strategy_hpp

class Strategy {
    public:
        // Constructor
        Strategy(float frequency) : frequency(frequency) {};

        // Destructor
        ~Strategy() = default;

        virtual double getPeriodExcessReturn(int time) = 0;
        double computeSharpe(int start, int end);

    private:
        // Parameters
        float frequency;
};

#endif