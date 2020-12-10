//
// Created by vladyslav on 10.12.2020.
//

#ifndef L3_SPHERE_H
#define L3_SPHERE_H
#include "../utils/stb_image.h"

#include <vector>
#include <GL/glew.h>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION

class Sphere {
private:
    std::string texturePath;
    unsigned int texture;

    unsigned int VAO, VBO, EBO;

    Shader* shader;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int sector;
    unsigned int stack;
    float radius;


public:
    Sphere(std::string, Shader*, unsigned int, unsigned int, float);
    void generateVertices();
    void generateIndices();
    void loadTexture();
    void bindAttributes();
};


#endif //L3_SPHERE_H
