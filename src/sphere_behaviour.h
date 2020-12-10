//
// Created by vladyslav on 10.12.2020.
//

#ifndef L3_SPHERE_BEHAVIOUR_H
#define L3_SPHERE_BEHAVIOUR_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class SphereBehaviour {
public:
    static glm::mat4  sunBehaviour();
    static glm::mat4 venusBehaviour();
};


#endif //L3_SPHERE_BEHAVIOUR_H
