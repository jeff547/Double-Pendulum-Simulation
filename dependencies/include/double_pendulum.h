#ifndef DOUBLE_PENDULUM_H
#define DOUBLE_PENDULUM_H

#include "ball.h"
#include "rod.h"
#include <glm/glm.hpp>
#include "ode.h"
#include <boost/numeric/odeint.hpp>

using namespace boost::numeric::odeint;

class DoublePendulum
{
public:
    DoublePendulum(glm::vec2 position, double mass_1, double mass_2, float radius_1, float radius_2, glm::vec3 color_1, glm::vec3 color_2,
                   float length_1, float length_2, double theta1, double theta2, double omega1, double omega2);
    void update(float time, float dt);
    void render(Shader &shader);
    void debugLog();

private:
    DoublePendulumMotion DP_motion_equations; // 1st order ODEs defining double pendulum's motion
    runge_kutta_cash_karp54<std::vector<double>> stepper;
    std::vector<double> state; // {angle_1, angular_velocity_1, angle_2, angular_velocity_2}
    Ball pivot;                // pivot of the pendulum system
    Ball bob_1;                // bob of the 1st pendulum
    Ball bob_2;                // bob of the 2nd pendulum
    Rod rod_1;
    Rod rod_2;
    glm::vec2 position; // pivot point of the double pendulum system
    float length_1;     // length of the 1st rod
    float length_2;     // length of the 2nd rod
};

#endif