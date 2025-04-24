#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <iostream>
using namespace std;

void framebuffer_size_callbacK(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float mixValue{0.0f};
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  // glfw: initalize and configure
  // -----------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // glfw: window creation
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

  // initalize data
  // --------------
  glEnable(GL_DEPTH_TEST);

  // rectangle vertices
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, -1.0f, -1.0f),
      glm::vec3(-4.0f, 1.0f, -1.5f),
  };

  // VAO and VBO
  unsigned int VBO,
      VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind VAO
  glBindVertexArray(VAO);

  // copy vertices into buffers
  // --------------------------
  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // EBO

  // configure attribute pointers
  // --------------------------
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // initialize textures
  unsigned int texture1, texture2;
  // texture 1
  // ---------
  glGenTextures(1, &texture1);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // texture settings
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load textures
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("images/earth.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    cout << "Failed to load texture 1" << '\n';
  }
  stbi_image_free(data);

  // texture 2
  // ---------
  glGenTextures(1, &texture2);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // texture settings
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("images/moon.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    cout << "Failed to load texture 2" << '\n';
  }
  stbi_image_free(data);

  // unbind buffers
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  shader.use();
  glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
  shader.setInt("texture2", 1);
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // esc -> exit
    processInput(window);

    // render background
    glClearColor(0.0f, 0.0f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // active shader
    shader.use();
    // time
    float timeValue = glfwGetTime();

    // apply 3D perspective
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // pass to shader
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    // render traingle
    glBindVertexArray(VAO);
    for (unsigned int i{0}; i < 3; i++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      if (i == 0)
      {
        model = glm::rotate(model, 1.2f * timeValue, glm::vec3(0.2f, 0.6f, 0.1f));
        shader.setFloat("mixValue", 0.0f);
      }
      else
      {
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, -1 * timeValue + glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(0.7f));
        shader.setFloat("mixValue", 1.0f);
      }
      shader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // swap buffers, handle IO
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // clear all resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  shader._delete();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callbacK(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, height, width);
}
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}