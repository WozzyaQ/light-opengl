#ifndef L3_LOGIC_H
#define L3_LOGIC_H
#include <utility>
#include "sphere.h"
#include "camera.h"
class Logic {
private:
    std::vector<Sphere*> spheres;
public:
    explicit Logic(std::vector<Sphere*>&);
    void run(Camera*, int, int);
};


#endif //L3_LOGIC_H
