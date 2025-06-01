#include "double_pendulum.h"
#include <cmath>
#include <boost/numeric/odeint.hpp>
#include "shader.h"
#include "ball.h"

using namespace boost::numeric::odeint;

DoublePendulum::DoublePendulum(glm::vec2 position, double mass_1, double mass_2, float radius_1, float radius_2,
                               glm::vec3 color_1, glm::vec3 color_2, float length_1, float length_2, double theta1, double theta2,
                               double omega1, double omega2)
    : DP_motion_equations(mass_1, mass_2, length_1, length_2, 9.81),
      stepper(),
      state({theta1, omega1, theta2, omega2}),
      pivot(position, 1.0f, 0.03f, glm::vec3(1.0f, 1.0f, 1.0f)),
      bob_1(position, mass_1, radius_1, color_1),
      bob_2(position, mass_2, radius_2, color_2),
      rod_1(position, 1.0f, length_1, glm::vec3(1.0f, 1.0f, 1.0f), theta1),
      rod_2(position, 1.0f, length_2, glm::vec3(1.0f, 1.0f, 1.0f), theta2),
      position(position), length_1(length_1), length_2(length_2) {}

void DoublePendulum::update(float time, float dt)
{
  // step ODEs
  stepper.do_step(DP_motion_equations, state, time, dt);
  // update XY coordinates
  // ------------------------
  // bob 1
  bob_1.position.x = position.x + length_1 * sin(state[0]);
  bob_1.position.y = position.y - length_1 * cos(state[0]);
  // bob 2
  bob_2.position.x = bob_1.position.x + length_2 * sin(state[2]);
  bob_2.position.y = bob_1.position.y - length_2 * cos(state[2]);
  // rods
  rod_1.angle = state[0];
  rod_2.angle = state[2];
  // rod 2
  rod_2.position = bob_1.position;
}

void DoublePendulum::render(Shader &shader)
{
  // render pivot
  pivot.render(shader);
  // render rods
  rod_1.render(shader);
  rod_2.render(shader);
  // render bobs
  bob_1.render(shader);
  bob_2.render(shader);
}

void DoublePendulum::debugLog()
{
  std::cout << "Bob 1: (" << bob_1.position.x << ", " << bob_1.position.y
            << ")         Bob 2: (" << bob_2.position.x << ", " << bob_2.position.y << ")\n";
}
