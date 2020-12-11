//
// Created by vladyslav on 10.12.2020.
//
#ifndef L3_ENGINE_H
#define L3_ENGINE_H

#include "logic.h"
#include "inputhandler.h"

class Engine {
private:
    Window* window;
    Logic* logic{};
    Camera* camera;

public:
    Engine();
    Engine(const std::string&, Camera*, int, int);
    void init();
    void loop();
    void loadLogic(Logic*);
};


#endif //L3_ENGINE_H
