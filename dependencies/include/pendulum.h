#ifndef PENDULUM_H
#define PENDULUM_H

#include "ball.h"
#include "rigidbody.h"
#include <glm/glm.hpp>
#include <iostream>

class DoublePendulum
{
public:
    DoublePendulum(glm::vec2 pivot_1, glm::vec2 pivot_2, double mass_1, double mass_2, float radius_1, float radius_2, glm::vec3 color_1, glm::vec3 color_2,
                   float length_1, float length_2, double theta1, double theta2, double omega1, double omega2);
    void update(float dT);
    void render(Shader &shader);
    

private:
    Ball bob_1;        // bob of the 1st pendulum
    Ball bob_2;        // bob of the 2nd pendulum
    glm::vec2 pivot_1; // pivot point of the 1st pendulum
    glm::vec2 pivot_2; // pivot point of the 2nd pendulum
    float length_1;    // length of the 1st rod
    float length_2;    // length of the 2nd rod
    double theta1;     // angle of the 1st pendulum
    double theta2;     // angle of the 2nd pendulum
    double omega1;     // angular velocity of the 1st pendulum
    double omega2;     // angular velocity of the 2nd pendulum
    double alpha1;     // angular acceleration of the 1st pendulum
    double alpha2;     // angular acceleration of the 2nd pendulum
};

#endif