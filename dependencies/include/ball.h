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
    float radius;
    glm::vec3 color;

    Ball(glm::vec2 pos, float m, float r, glm::vec3 c);
    ~Ball();

    void render(Shader &shader);
    void update(float dt);
    void reset();
    void debugLog();

private:
    static unsigned int VAO;
    static void initRenderData();
};

#endif