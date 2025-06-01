#include <vector>
#include <cmath>
#include <boost/numeric/odeint.hpp>
#include "ode.h"

DoublePendulumMotion::DoublePendulumMotion(float m1, float m2, float L1, float L2, float g)
    : m1(m1), m2(m2), L1(L1), L2(L2), g(g) {}

void DoublePendulumMotion::operator()(const std::vector<double> &x, std::vector<double> &dxdt, double t) const
{
    double theta1 = x[0], omega1 = x[1], theta2 = x[2], omega2 = x[3];

    double cos_theta = cos(theta1 - theta2);
    double sin_theta = sin(theta1 - theta2);

    double b11 = L1 * (m1 + m2);
    double b12 = m2 * L2 * cos_theta;
    double b21 = -L2 * cos_theta;
    double b22 = -L2;

    double c1 = (m1 + m2) * g * sin(theta1) + m2 * L2 * pow(omega2, 2) * sin_theta;
    double c2 = pow(omega1, 2) * L1 * sin_theta - g * sin(theta2);

    double A = b11 * b22 - b12 * b21;

    double alpha1 = (-c1 * b22 + c2 * b12) / A;
    double alpha2 = (-c2 * b11 + c1 * b21) / A;

    dxdt[0] = omega1;
    dxdt[1] = alpha1;
    dxdt[2] = omega2;
    dxdt[3] = alpha2;
}
