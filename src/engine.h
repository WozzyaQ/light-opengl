#ifndef L3_ENGINE_H
#define L3_ENGINE_H

#include "camera.h"
#include "sphere.h"
#include "window.h"
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
