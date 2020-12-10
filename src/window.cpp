#include "window.h"

Window::Window() {
    this->title = "Default Title";
    this->width = 1366;
    this->height = 720;
}

Window::Window(const std::string& title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
}

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!checkIfWindowHandleIsOk()) exit(-1);
    glfwMakeContextCurrent(windowHandle);

    glfwSetFramebufferSizeCallback(windowHandle, framebufferSizeCallback);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Window::checkIfWindowHandleIsOk() {
    if (windowHandle == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *Window::getWindowHandle() {
    return windowHandle;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}
