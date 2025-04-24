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

const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
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
    unsigned int fragmentShaderOrange{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShaderOrange);
    // other fragment shader
    unsigned int fragmentShaderYellow{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShaderYellow);

    // error handling
    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
        cout << "ERROR:ORANGE:FRAGMENT:VERTEX:COMPILATION_FAILED\n"
             << infoLog << '\n';
        return -1;
    }
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        cout << "ERROR:YELLOW:FRAGMENT:VERTEX:COMPILATION_FAILED\n"
             << infoLog << '\n';
        return -1;
    }

    // orange shader
    unsigned int orangeShaderProgram{glCreateProgram()};
    // link shaders
    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, fragmentShaderOrange);
    glLinkProgram(orangeShaderProgram);
    // error handling
    glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(orangeShaderProgram, 512, NULL, infoLog);
        cout << "ERROR:ORANGE:SHADER:PROGRAM:COMPILATION_FAILED\n"
             << infoLog << '\n';
        return -1;
    }

    // yellow shader
    unsigned int yellowShaderProgram{glCreateProgram()};
    // link shaders
    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, fragmentShaderYellow);
    glLinkProgram(yellowShaderProgram);
    // error handling
    glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
        cout << "ERROR:YELLLOW:SHADER:PROGRAM:COMPILATION_FAILED\n"
             << infoLog << '\n';
        return -1;
    }

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    // initalize data
    // --------------
    float vertices[] = {
        0.5f, 0.0f, 0.0f,  // i=0
        0.0f, 0.5f, 0.0f,  // i=1
        -0.5f, 0.0f, 0.0f, // i=2
        0.0f, -0.5f, 0.0f  // i=3
    };
    unsigned int firstIndices[] = {
        0, 1, 3 // first triangle
    };
    unsigned int secondIndices[] = {
        1, 2, 3 // second triangle
    };

    // VAO and VBO
    unsigned int VBOs[2], VAOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);
    // first triangle
    // --------------
    // bind VAO
    glBindVertexArray(VAOs[0]);
    // copy vertices into buffers
    // --------------------------
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(firstIndices), firstIndices, GL_STATIC_DRAW);
    // configure attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // second triangle
    // --------------
    // bind VAO
    glBindVertexArray(VAOs[1]);
    // copy vertices into buffers
    // --------------------------
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(secondIndices), secondIndices, GL_STATIC_DRAW);
    // configure attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // esc -> exit
        processInput(window);

        // render background
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);
        // render triangle 1
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(yellowShaderProgram);
        // render triangle 2
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // swap buffers, handle IO
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clear all resources
    // -------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(2, EBOs);
    glDeleteProgram(orangeShaderProgram);
    glDeleteProgram(yellowShaderProgram);

    // end
    // ---
    glfwTerminate();
    return 0;
}