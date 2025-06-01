#ifndef ODE_H
#define ODE_H

#include <vector>

// define system of odes
struct DoublePendulumMotion
{
    float m1, m2, L1, L2, g;

    DoublePendulumMotion(float m1, float m2, float L1, float L2, float g);

    // calculates equations
    void operator()(const std::vector<double> &x, std::vector<double> &dxdt, double t) const;
};

#endif