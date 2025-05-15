#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "ball.h"

unsigned int Ball::VAO = 0;

Ball::Ball(glm::vec2 pos, float m, float r, glm::vec3 c) : RigidBody(m, pos), radius(r), color(c)
{
    if (VAO == 0)
    {
        initRenderData();
    }
};

Ball::~Ball()
{
    glDeleteVertexArrays(1, &VAO);
}

// debug log
void Ball::debugLog()
{
    std::cout << "y-velocity: " << velocity.y << ",   y_position: " << position.y
              << ",   x-velocity: " << velocity.x << ",   x_position: " << position.x << '\n';
}

void Ball::update(float dt)
{
    RigidBody::update(dt);

    // floor bounce
    if (position.y - radius < 0.0f)
    {
        position.y = radius;
        velocity.y *= -0.95;
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
    // initialze vertices
    std::vector<float> vertices = {0.0f, 0.0f};
    for (int i{0}; i <= 100; ++i)
    {
        float angle = (2 * M_PI * i) / 100;
        vertices.push_back(cos(angle));
        vertices.push_back(sin(angle));
    }

    // initialize VAO/VBO
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
}

void Ball::render(Shader &shader)
{
    shader.use();

    // configure model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));

    shader.setMat4("model", model);
    shader.setVec3("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 101 + 2);
    glBindVertexArray(0);
}
