#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rigidbody.h"

RigidBody::RigidBody(float m, glm::vec2 pos) : mass(m), position(pos) {}

void RigidBody::update(float dt)
{
    position += velocity * dt + 0.5f * acceleration * (dt * dt);
    velocity += acceleration * dt;
    acceleration = glm::vec2(0.0f);
}
