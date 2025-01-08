#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int width = 1024;
int heihgt = 768;

void framebuffer_size_callback(GLFWwindow* pwindow, int width, int height) {
    
    glViewport(0, 0, width, height); 
}

int main() {

    if (!glfwInit()) {
        std::cerr << "Ошибка инициализации GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, heihgt, "My first window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Ошибка создания окна" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Ошибка инициализации GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetWindowShouldClose(window, glfwGetKey(window, GLFW_KEY_ESCAPE));
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


