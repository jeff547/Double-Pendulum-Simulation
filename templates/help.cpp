#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

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

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

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

  int success;
  char infoLog[512];

  // initialize shaders
  // ------------------------
  // vertex shader
  unsigned int vertexShader{glCreateShader(GL_VERTEX_SHADER)};
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // error handling
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    cout << "ERROR:SHADER:VERTEX:COMPILATION_FAILED\n"
         << infoLog << '\n';
    return -1;
  }

  // fragment shader
  unsigned int fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // error handling
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    cout << "ERROR:FRAGMENT:VERTEX:COMPILATION_FAILED\n"
         << infoLog << '\n';
    return -1;
  }

  // link shaders
  unsigned int shaderProgram{glCreateProgram()};
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // error handling
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    cout << "ERROR:SHADER:PROGRAM:COMPILATION_FAILED\n"
         << infoLog << '\n';
    return -1;
  }
  // delete shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // initalize data
  // --------------

  // rectangle vertices
  float vertices[] = {
      0.5f, 0.5f, 0.0f,   // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f   // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  // diamond vertices
  float vertices[] = {
      0.5f, 0.0f, 0.0f,  // i=0
      0.0f, 0.5f, 0.0f,  // i=1
      -0.5f, 0.0f, 0.0f, // i=2
      0.0f, -0.5f, 0.0f  // i=3
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  // VAO and VBO
  unsigned int VBO, VAO, EBO;
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // configure attribute pointers
  // --------------------------
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // unbind buffers
  // --------------
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // esc -> exit
    processInput(window);

    // render background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render traingle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers, handle IO
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // clear all resources
  // -------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  // end
  // ---
  glfwTerminate();
  return 0;
}