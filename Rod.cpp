#include "rod.h"
#include <glad/glad.h>
#include <iostream>

Rod::Rod(glm::vec2 position, float mass, float length, glm::vec3 color, float angle)
    : RigidBody(mass, position), color(color), angle(angle), length(length)
{
    initRenderData();
}

Rod::~Rod()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Rod::initRenderData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Rod::update(float dt)
{
    RigidBody::update(dt);
}

void Rod::render(Shader &shader)
{
    // Update this rod's vertex data
    float vertices[4] = {
        position.x, position.y,
        position.x + length * sin(angle),
        position.y - length * cos(angle)};

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    shader.setVec3("color", color);

    glBindVertexArray(VAO);
    glLineWidth(10.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glLineWidth(1.0f);
    glBindVertexArray(0);
}