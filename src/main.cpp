#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"
#include "shader.h"
#include "camera.h"

int width = 1366, height = 720;

float lastX = (float)width/2, lastY = (float)height/2;


bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;



Camera camera(glm::vec3(0.0f, 30.0f, 30.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void fillVerticesOfSphere(std::vector<float> &vertices, float radius);
void fillIndicesOfSphere(std::vector<unsigned int> &indices);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Usual staff", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewInit();



    const char* vertexPathSphere = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.vert";
    const char* fragmentPathSphere = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.frag";
    Shader sphereShader(vertexPathSphere, fragmentPathSphere);



    std::vector<float> verticesOfSphere;
    std::vector<unsigned int> indicesOfSphere;

    std::vector<float> sunVer;
    std::vector<unsigned int> sunInd;


    fillVerticesOfSphere(verticesOfSphere, 0.5f);
    fillIndicesOfSphere(indicesOfSphere);

    fillVerticesOfSphere(sunVer, 7.0f);
    fillIndicesOfSphere(sunInd);



    unsigned int texture[2];
    glGenTextures(2, texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int imageWidth, imageHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    const char* imagePath1 = "/home/vladyslav/CLionProjects/opengl_light/res/venus.jpg";
    unsigned char *data = stbi_load(imagePath1, &imageWidth, &imageHeight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(texture[0]);
    }
    else std::cout << "Failed to load texture" << std::endl;


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
///////////////////////////////////////////////////////
    imagePath1 = "/home/vladyslav/CLionProjects/opengl_light/res/sun.jpg";
    data = stbi_load(imagePath1, &imageWidth, &imageHeight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(texture[1]);
    }
    else std::cout << "Failed to load texture" << std::endl;

    stbi_image_free(data);
///////////////////////////////////////////////////

    // створюємо об'єкт вершинного буферу та об'єкт вершинного масиву
    unsigned int VAO[2], VBO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);




    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, verticesOfSphere.size() * sizeof(float), &verticesOfSphere[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesOfSphere.size() * sizeof(float), &indicesOfSphere[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sunVer.size() * sizeof(float), &sunVer[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sunInd.size() * sizeof(float), &sunInd[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);


    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        glClearColor(0.0f, 0.0f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        sphereShader.use();
        sphereShader.setInt("texture1", 0);

        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

        view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        sphereShader.setMat4("view", view);

        projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.001f, 100.0f);
        sphereShader.setMat4("projection", projection);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime()*20*glm::radians((float)2.0), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(20.0f,-5.0f,1.0f));
        model = glm::rotate(model, (float)glfwGetTime()*0.5f*glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        sphereShader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, indicesOfSphere.size(), GL_UNSIGNED_INT, (void*)0);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
        sphereShader.setInt("texture1", 1);

        view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        sphereShader.setMat4("view", view);

        projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.001f, 100.0f);
        sphereShader.setMat4("projection", projection);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f,-5.0f,1.0f));
        model = glm::rotate(model, (float)-glfwGetTime()*10*glm::radians((float)1.0), glm::vec3(0.0f, 1.0f, 0.0f));


        sphereShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, indicesOfSphere.size(), GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;
    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void fillVerticesOfSphere(std::vector<float> &vertices, float radius)
{
    float x, y, z, xy;
    float s, t;

    unsigned int sectorCount = 50;
    unsigned int stackCount = 50;
//    float radius = 0.5;

    float sectorStep = 2.0 * M_PI / (float)sectorCount;
    float stackStep = M_PI / (float)stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2.0 - (float)i * stackStep;
        xy = (float)radius * cos(stackAngle);
        z = (float)radius * sin(stackAngle);
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = (float)j * sectorStep;
            x = xy * cos(sectorAngle);
            y = xy * sin(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }
}

void fillIndicesOfSphere(std::vector<unsigned int> &indices)
{
    int k1, k2;

    unsigned int stackCount = 50;
    unsigned int sectorCount = 50;

    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if(i != stackCount - 1)
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}