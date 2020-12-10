//
// Created by vladyslav on 10.12.2020.
//

#include "sphere_behaviour.h"




glm::mat4 SphereBehaviour::sunBehaviour() {

    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime()*20*glm::radians((float)2.0), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(20.0f,-5.0f,1.0f));
    model = glm::rotate(model, (float)glfwGetTime()*0.5f*glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    return model;
}

glm::mat4 SphereBehaviour::venusBehaviour() {
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,-5.0f,1.0f));
    model = glm::rotate(model, (float)-glfwGetTime()*10*glm::radians((float)1.0), glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}
