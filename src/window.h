//
// Created by vladyslav on 10.12.2020.
//
#ifndef L3_WINDOW_H
#define L3_WINDOW_H

#include "shader.h"

class Window {
    int width{};
    int height{};
    std::string title;
    GLFWwindow* windowHandle;

    bool checkIfWindowHandleIsOk();
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    Window();
    Window(const std::string&, int, int);
    void init();
    GLFWwindow* getWindowHandle();
    int getWidth();
    int getHeight();

};


#endif //L3_WINDOW_H
