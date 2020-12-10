//
// Created by vladyslav on 10.12.2020.
//

#ifndef L3_INPUTHANDLER_H
#define L3_INPUTHANDLER_H

#include "camera.h"
#include "window.h"
#include <GLFW/glfw3.h>

class InputHandler {
private:
    static GLFWwindow* windowHandle;
    static Window* winObj;

    static Camera* camera;
    static bool firstOpen;

    static float lastXPos;
    static float lastYPos;

public:
    static void setWindowHandle(Window*);
    static void setCamera(Camera*);
    static void inputHandle(float);
    static void mouseCallback(GLFWwindow*, double, double);
    static void scrollCallback(GLFWwindow*, double, double);
};


#endif //L3_INPUTHANDLER_H
