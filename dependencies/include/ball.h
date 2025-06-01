#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rigidbody.h"
#include "shader.h"

class Ball : public RigidBody
{
public:
    float radius;                     // radius of the ball
    glm::vec3 color;                  // color of the ball
    std::array<glm::vec2, 1000> path; // tracks the path of motion
    short index;

    Ball(glm::vec2 position, float mass, float radius, glm::vec3 color);
    ~Ball();

    void render(Shader &shader);
    void update(float dt);
    void reset();
    void debugLog();

private:
    unsigned int ballVAO, ballVBO, pathVAO, pathVBO;
    void initRenderData();
};

#endif