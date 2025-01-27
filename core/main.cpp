#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // ������������ ���������� � �������� ���� ������� ����� ���� ��������� ������, ������� ��������� ��� ��� location = 0
"out vec4 vertexColor;\n" // ���������� �������� ����������, �������� ����, ������� ����� �������� �� ����������� ������
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // �������� ��������, ��� � ����������� ���������� ���� vec4 �� �������� �������� ���������� ���� vec3
"   vertexColor = vec4(0.0, 0.0, 1.0, 1.0);\n" // ������ �������� ����� ��� �������� ����������
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n" // ������� ���������� �� ���������� ������� (����� �� ��� � ����� �� ���)
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

int main() {
    // glfw: ������������� � ����������������
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: �������� ����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My first window", nullptr, nullptr);
    if (!window) {
        std::cerr << "������ �������� ����" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: �������� ���� ���������� �� OpenGL-�������
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "������ ������������� GLAD" << std::endl;
        return -1;
    }

    // ��������� ������
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // �������� �� ������� ������ �������������� ���������� �������
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ����������� ������
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // �������� �� ������� ������ �������������� ������������ �������
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ���������� ��������
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // �������� �� ������� ������ ���������� ��������
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ���������� ������ (� �������) � ��������� ��������� ���������
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,  // ������ ����� �������
     0.5f, -0.5f, 0.0f,  // ������ ������ �������
     0.0f,  0.5f, 0.0f   // ������� �������
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �������� ��������, ��� ������ �������� ���������, ����� glVertexAttribPointer() ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� ����� �� ����� �������� ��������� �������
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  
    // �� ������ �������� �������� VAO ����� �����, ����� ������ ������ VAO �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
    // ����������� ������ VAO ������� ������ glBindVertexArray(), ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
    glBindVertexArray(0);

    // ���������������� ��������� ������ ��� ��������� ��������� � ������ �������
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // ���� ����������
    while (!glfwWindowShouldClose(window)) 
    {
        // ��������� �����
        processInput(window);

        // ���������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ��� ������ �����������
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // ��������� � ��� ���� ������ ���� VAO, �� ��� ������������� ��������� ��� ������ ��� (�� �� ������� ���, ����� �� ���� ������� ��������������)
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // �� ����� ������ ��� ��� ����������

        // glfw: ����� ���������� front- � back-�������. ������������ ������� �����/������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: ����������, ������������ ���� ����� ��������������� GLFW-��������
    glfwTerminate();
    return 0;
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ ���� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* pwindow)
{
    if (glfwGetKey(pwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pwindow, true);
    }

}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������

void framebuffer_size_callback(GLFWwindow* pwindow, int width, int height)
{
    // ����������, ��� ���� ��������� ������������� ����� �������� ����.
    // �������� ��������, ������ ���� �� Retina-�������� ����� ����������� ������, ��� ������� � ���������
    glViewport(0, 0, width, height);
}


