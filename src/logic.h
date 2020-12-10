#ifndef L3_LOGIC_H
#define L3_LOGIC_H
#include <utility>
#include "sphere.h"

class Logic {
private:
    std::vector<Sphere*> spheres;
public:
    explicit Logic(std::vector<Sphere*>&);
};


#endif //L3_LOGIC_H
