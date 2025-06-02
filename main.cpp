#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <iostream>
#include "ball.h"
#include "lab.h"
using namespace std;

void framebuffer_size_callbacK(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Lab &lab);

int main()
{
  // glfw: initalize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // glfw: window creation
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "OpenGL", nullptr, nullptr);

  if (window == NULL)
  {
    cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callbacK);

  // initialze GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "Failed to initialize GLAD" << '\n';
    return -1;
  }

  // Enable Blending (Transparency)
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // initialize shaders
  Shader shader("shaders/vertex.txt", "shaders/fragment.txt");

  // Physics Setup
  Lab lab;
  float tI = 0.0f;
  float gravity = 9.8f;
  float world_size = 10.0f;

  // initialize projection
  int window_height, window_width;
  glfwGetFramebufferSize(window, &window_width, &window_height);
  float aspect_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);
  glm::mat4 projection;

  if (aspect_ratio > 1.0f)
  {
    projection = glm::ortho(-world_size * aspect_ratio, world_size * aspect_ratio, -world_size, world_size, -1.0f, 1.0f);
  }
  else
  {
    projection = glm::ortho(-world_size, world_size, -world_size / aspect_ratio, world_size / aspect_ratio, -1.0f, 1.0f);
  }

  shader.use();
  shader.setMat4("projection", projection);

  // initialize double pendulum parameters
  glm::vec2 pos{0.0f, 0.0f};

  double mass_1 = 10.0;
  double mass_2 = 10.0;

  double radius = 0.25;

  float length_1 = 4.0;
  float length_2 = 4.0;

  double theta_1 = 3 * M_PI_4;
  double theta_2 = 3 * M_PI_4;

  double omega = 0.0;

  glm::vec3 blue{0.4f, 0.7f, 1.0f};
  glm::vec3 orange{1.0f, 0.7f, 0.3f};

  lab.Pendulums.push_back(new DoublePendulum(pos, mass_1, mass_2, radius, radius, blue, orange, length_1, length_2, theta_1, theta_2, omega, omega, gravity));

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // initialize
    processInput(window, lab);
    float tF = glfwGetTime();
    float dt = tF - tI;
    tI = tF;
    // render
    lab.update(dt);
    lab.debugLog();

    // render background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw
    shader.use();
    lab.render(shader);

    // swap buffers, handle IO
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // clear all resources
  shader._delete();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callbacK(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window, Lab &lab)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
  {
    lab.reset();
    glfwSetTime(0.0f);
  }
}