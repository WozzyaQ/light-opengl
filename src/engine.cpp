#include "engine.h"


Engine::Engine() {
    this->window = new Window();

}

Engine::Engine(const std::string& title, Camera* camera, int width, int height) {
    this->window = new Window(title, width, height);
    this->camera = camera;
}

void Engine::init() {
    this->window->init();
    InputHandler::setWindowHandle(window);
    InputHandler::setCamera(camera);
}

void Engine::loop() {

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!glfwWindowShouldClose(window->getWindowHandle()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputHandler::inputHandle(deltaTime);

        glfwSetCursorPosCallback(window->getWindowHandle(), InputHandler::mouseCallback);
        glfwSetScrollCallback(window->getWindowHandle(), InputHandler::scrollCallback);

        glClearColor(0.0f, 0.0f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





        glfwSwapBuffers(window->getWindowHandle());
        glfwPollEvents();
    }
}

void Engine::loadLogic(Logic* logic) {
    this->logic = logic;
}

