#ifndef CLOCK_CESAR_HPP
#define CLOCK_CESAR_HPP

class Clock
{
private:
    unsigned int cycleCount;
    unsigned int frequency; // em Hertz

public:
    void tick();
    unsigned int getCycleCount() const;
};

#endif