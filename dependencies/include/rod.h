#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "rigidbody.h"

class Rod : public RigidBody
{
public:
    unsigned int VAO, VBO;

    glm::vec3 color;
    float angle;
    float length;

    Rod(glm::vec2 position, float mass, float length, glm::vec3 color, float angle);
    ~Rod();

    void update(float dt);
    void render(Shader &shader);

private:
    void initRenderData();
};