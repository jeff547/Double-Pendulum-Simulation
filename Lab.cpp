#include "shader.h"
#include <iostream>
#include "ball.h"
#include "lab.h"

void Lab::render(Shader &shader)
{
    for (Ball *ball : balls)
    {
        ball->render(shader);
    }
}

void Lab::update(float dt)
{
    for (Ball *ball : balls)
    {
        ball->acceleration += gravitationalAcceleration;

        ball->update(dt);
    }
}

void Lab::reset()
{
    for (Ball *ball : balls)
    {
        ball->reset();
    }
}

void Lab::debugLog()
{
    for (Ball *ball : balls)
    {
        ball->debugLog();
    }
}