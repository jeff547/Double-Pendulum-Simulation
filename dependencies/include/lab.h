#ifndef LAB_H
#define LAB_H

#include "shader.h"
#include <iostream>
#include "ball.h"
#include "double_pendulum.h"

class Lab
{
public:
    // std::vector<Ball *> balls;
    std::vector<DoublePendulum *> Pendulums;
    float time = 0;
    // glm::vec2 gravitationalAcceleration = glm::vec2(0.0f, -981.0f);

    void update(float dt);
    void render(Shader &shader);
    void debugLog();
    void reset();
};

#endif