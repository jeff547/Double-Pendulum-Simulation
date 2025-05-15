#ifndef RIGIDBODY
#define RIGIDBODY

#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RigidBody
{
public:
    float mass;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    RigidBody(float m = 1.0f, glm::vec2 pos = glm::vec2(300.0f, 300.0f));

    // updates every frame
    void update(float dt);
};

#endif