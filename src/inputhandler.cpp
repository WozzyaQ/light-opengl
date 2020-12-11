//
// Created by vladyslav on 10.12.2020.
//
#include "inputhandler.h"


GLFWwindow* InputHandler::windowHandle = nullptr;
Window* InputHandler::winObj = nullptr;
Camera* InputHandler::camera = nullptr;
bool InputHandler::firstOpen = false;
float InputHandler::lastXPos = 0.0f;
float InputHandler::lastYPos = 0.0f;


void InputHandler::setWindowHandle(Window* window) {
    InputHandler::windowHandle = window->getWindowHandle();
    InputHandler::winObj = window;

    lastXPos = (float)window->getWidth()/2;
    lastYPos = (float)window->getHeight()/2;
}

void InputHandler::inputHandle(float dt) {
    if(glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(windowHandle, true);
    if(glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, dt);
}

void InputHandler::setCamera(Camera * camera) {
    InputHandler::camera = camera;
}

void InputHandler::mouseCallback(GLFWwindow * window, double xpos, double ypos) {
    if(firstOpen)
    {
        lastXPos = xpos;
        lastYPos = ypos;
        firstOpen = false;
    }
    float xoffset = (float)xpos - lastXPos;
    float yoffset = lastYPos- (float)ypos;
    lastXPos = (float)xpos;
    lastYPos = (float)ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->ProcessMouseScroll(yoffset);
}

