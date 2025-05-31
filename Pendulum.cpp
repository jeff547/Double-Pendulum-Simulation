#include "pendulum.h"
#include <cmath>
#include "shader.h"
#include "ball.h"

DoublePendulum::DoublePendulum(glm::vec2 pivot_1, glm::vec2 pivot_2, double mass_1, double mass_2, float radius_1, float radius_2, glm::vec3 color_1, glm::vec3 color_2,
                               float length_1, float length_2, double theta1, double theta2, double omega1, double omega2)
    : bob_1(pivot_1 + glm::vec2(length_1 * sin(theta1), length_1 * cos(theta1)), mass_1, radius_1, color_1),
      bob_2(pivot_2 + glm::vec2(length_2 * sin(theta2), length_2 * cos(theta2)), mass_2, radius_2, color_2),
      pivot_1(pivot_1), pivot_2(pivot_2), length_1(length_1), length_2(length_2),
      theta1(theta1), theta2(theta2), omega1(omega1), omega2(omega2) {}

void DoublePendulum::update(float dT)
{
    // update XY coordinates
    // ------------------------
    // update position bob 1
    bob_1.position.x = pivot_1.x + length_1 * sin(theta1);
    bob_1.position.y = pivot_1.y + length_1 * cos(theta1);
    // update position bob 2
    bob_2.position.x = pivot_2.x + length_2 * sin(theta2);
    bob_2.position.y = pivot_2.y + length_2 * cos(theta2);
    /// update velocity bob 1
    bob_1.velocity.x = length_1 * omega1 * cos(theta1);
    bob_1.velocity.y = -length_1 * omega1 * sin(theta1);
    /// update velocity bob 2
    bob_2.velocity.x = length_2 * omega2 * cos(theta2);
    bob_2.velocity.y = -length_2 * omega2 * sin(theta2);

    // update angle and velocity

    // update angular acceleration
}
