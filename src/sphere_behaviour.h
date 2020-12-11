//
// Created by vladyslav on 10.12.2020.
//

#ifndef L3_SPHERE_BEHAVIOUR_H
#define L3_SPHERE_BEHAVIOUR_H
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "shader.h"


class SphereBehaviour {
    static glm::mat4 model;
    static glm::mat4 view;
    static glm::mat4 projection;
public:
    static void sunBehaviour(const Shader*, int, Camera*, int, int);
    static void venusBehaviour(const Shader*, int, Camera*, int, int);
    static void initMatrices();
};


#endif //L3_SPHERE_BEHAVIOUR_H
