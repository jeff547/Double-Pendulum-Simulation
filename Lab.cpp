#include "shader.h"
#include <iostream>
#include "lab.h"

void Lab::render(Shader &shader)
{
    for (DoublePendulum *dp : Pendulums)
    {
        dp->render(shader);
    }
    // for (Ball *ball : balls)
    // {
    //     ball->render(shader);
    // }
}

void Lab::update(float dt)
{
    time += dt;
    for (DoublePendulum *dp : Pendulums)
    {
        dp->update(time, dt);
    }
    // for (Ball *ball : balls)
    // {
    //     ball->acceleration += gravitationalAcceleration;

    //     ball->update(dt);
    // }
}

void Lab::reset()
{
    // for (Ball *ball : balls)
    // {
    //     ball->reset();
    // }
}

void Lab::debugLog()
{
    std::cout << "Time: " << time << "  -->  ";
    for (DoublePendulum *dp : Pendulums)
    {
        dp->debugLog();
    }
    // for (Ball *ball : balls)
    // {
    //     ball->debugLog();
    // }
}