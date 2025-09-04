#include <iostream>
#include "shader.h"
#include "ball.h"

Ball::Ball(glm::vec2 position, float mass, float radius, glm::vec3 color) : RigidBody(mass, position), radius(radius), color(color)
{
    initRenderData();
};

Ball::~Ball()
{
    glDeleteVertexArrays(1, &ballVAO);
    glDeleteBuffers(1, &ballVBO);
    glDeleteVertexArrays(1, &pathVAO);
    glDeleteBuffers(1, &pathVBO);
}

void Ball::debugLog()
{
    // std::cout << "y-velocity: " << velocity.y << ",   y_position: " << position.y
    //           << ",   x-velocity: " << velocity.x << ",   x_position: " << position.x << '\n';
    // std::cout << "Path: (" << path[index].x << ", " << path[index].y << ")     ";
}

void Ball::update(float dt, bool draw_path)
{
    RigidBody::update(dt);
    if (draw_path)
    {
        path.push_back(position);
    }
}

void Ball::reset()
{
    position.x = 400.0f;
    position.y = 700.0f;
    velocity *= 0;
}

void Ball::initRenderData()
{
    // initialze ball vertices
    std::vector<float> vertices = {0.0f, 0.0f};
    for (int i{0}; i <= 100; ++i)
    {
        float angle = (2 * M_PI * i) / 100;
        vertices.push_back(cos(angle));
        vertices.push_back(sin(angle));
    }

    // initialize ball VAO/VBO
    glGenVertexArrays(1, &ballVAO);
    glGenBuffers(1, &ballVBO);

    glBindVertexArray(ballVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // initialzie path VAO/VBO
    glGenVertexArrays(1, &pathVAO);
    glGenBuffers(1, &pathVBO);

    glBindVertexArray(pathVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pathVBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Ball::render(Shader &shader)
{
    shader.use();

    // Render Ball
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    shader.setMat4("model", model);
    shader.setVec4("color", glm::vec4(color, 1.0f));

    // Comment to Hide
    glBindVertexArray(ballVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 101 + 2);
    glBindVertexArray(0);

    // Render Path of motion
    if (path.size() > 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, pathVBO);
        glBufferData(GL_ARRAY_BUFFER, path.size() * sizeof(glm::vec2), path.data(), GL_DYNAMIC_DRAW);

        shader.setMat4("model", glm::mat4(1.0f));
        shader.setVec4("color", glm::vec4(color, 0.55f));

        glBindVertexArray(pathVAO);
        glDrawArrays(GL_LINE_STRIP, 0, path.size());
        glBindVertexArray(0);
    }
}
