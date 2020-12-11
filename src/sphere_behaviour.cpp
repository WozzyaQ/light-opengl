//
// Created by vladyslav on 10.12.2020.
//

#include "sphere_behaviour.h"


glm::mat4 SphereBehaviour::model = glm::mat4(0);
glm::mat4 SphereBehaviour::projection = glm::mat4(0);
glm::mat4 SphereBehaviour::view = glm::mat4(0);

void SphereBehaviour::venusBehaviour(const Shader* shader, int index, Camera* camera, int width, int height) {
    initMatrices();

    //light parameters
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
    glm::vec3 lightColor(1.0f, 0.5f, 1.0f);

    shader->use();
    shader->setInt("venusTexture",index);
    shader->setVec3("lightColor", lightColor);
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("viewPos", camera->Position);
    //view
    view = camera->GetViewMatrix();
    shader->setMat4("view", view);

    //projection
    projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.001f, 100.0f);
    shader->setMat4("projection", projection);

    //model
    model = glm::rotate(model, (float)glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime()*5*glm::radians((float)2.0), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(20.0f,-5.0f,1.0f));
    model = glm::rotate(model, (float)glfwGetTime()*0.5f*glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    shader->setMat4("model", model);
}

void SphereBehaviour::sunBehaviour(const Shader* shader, int index, Camera* camera, int width, int height) {
    initMatrices();
    //parameters
    glm::vec3 lightColor(1.0f, 0.5f, 1.0f);

    shader->use();
    shader->setInt("sunTexture",index);
    shader->setVec3("lightColor", lightColor);


    //view
    view = camera->GetViewMatrix();
    shader->setMat4("view", view);

    //projection
    projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.001f, 100.0f);
    shader->setMat4("projection", projection);

    //model
    model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
    model = glm::rotate(model, (float)-glfwGetTime()*10*glm::radians((float)1.0), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->setMat4("model", model);
}

void SphereBehaviour::initMatrices() {
    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
}
