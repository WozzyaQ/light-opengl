#include "logic.h"

Logic::Logic(std::vector<Sphere *>& spheres) {
    this->spheres = spheres;
}

void Logic::run(Camera* camera, int width, int height) {
    int index = 0;
    for(auto& sphere : spheres) {
        sphere->draw(index++, camera, width, height);
    }
}
