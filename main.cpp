#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <iostream>
#include "ball.h"
#include "lab.h"
using namespace std;

void framebuffer_size_callbacK(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Lab &lab);

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

int main()
{
  // glfw: initalize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // glfw: window creation
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
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

  // initialize shaders
  Shader shader("shaders/vertex.txt", "shaders/fragment.txt");

  // initialize projection
  // physics scale
  float world_size = 2.5f;
  glm::mat4 projection{glm::ortho(-world_size, world_size, -world_size, world_size, -1.0f, 1.0f)};
  shader.use();
  shader.setMat4("projection", projection);

  // initialize data
  Lab lab;
  glm::vec2 pos{0.0f, 1.0f};
  glm::vec3 color1{1.0f, 0.0f, 0.0f};
  glm::vec3 color2{0.0f, 1.0f, 0.0f};

  lab.Pendulums.push_back(new DoublePendulum(pos, 3.0, 2.0f, 0.15, 0.15, color1, color2, 1.0, 1.0, M_PI_2, M_PI_4, 0.0, 0.0));
  float tI = 0.0f;
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
    glClearColor(0.0f, 0.0f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
  glViewport(0, 0, height, width);
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