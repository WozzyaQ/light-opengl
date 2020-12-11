//
// Created by vladyslav on 10.12.2020.
//
#ifndef L3_LOGIC_H
#define L3_LOGIC_H
#include "sphere.h"
class Logic {
private:
    std::vector<Sphere*> spheres;
public:
    explicit Logic(std::vector<Sphere*>&);
    void run(Camera*, int, int);
};


#endif //L3_LOGIC_H
