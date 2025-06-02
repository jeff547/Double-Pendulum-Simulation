#ifndef BALL_H
#define BALL_H

#include "rigidbody.h"
#include "shader.h"

class Ball : public RigidBody
{
public:
    float radius;                // radius of the ball
    glm::vec3 color;             // color of the ball
    std::vector<glm::vec2> path; // tracks the path of motion
    size_t index;

    Ball(glm::vec2 position, float mass, float radius, glm::vec3 color);
    ~Ball();

    void render(Shader &shader);
    void update(float dt, bool draw_path);
    void reset();
    void debugLog();

private:
    unsigned int ballVAO, ballVBO, pathVAO, pathVBO;
    void initRenderData();
};

#endif