#include "sphere.h"

Sphere::Sphere(std::string texturePath, Shader* shader, unsigned int sector, unsigned int stack , float radius) {
    this->texturePath = texturePath;
    this->shader = shader;

    this->sector = sector;
    this->stack = stack;
    this->radius = radius;

    generateVertices();
    generateIndices();
    loadTexture();
    bindAttributes();

}

void Sphere::generateVertices() {
    float x, y, z, xy;
    float p, q;

    float sectorStep = 2.0 * M_PI / (float)sector;
    float stackStep = M_PI / (float)stack;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stack; ++i)
    {
        stackAngle = M_PI / 2.0 - (float)i * stackStep;
        xy = (float)radius * cos(stackAngle);
        z = (float)radius * sin(stackAngle);

        for(int j = 0; j <= sector; ++j)
        {
            sectorAngle = (float)j * sectorStep;
            x = xy * cos(sectorAngle);
            y = xy * sin(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            p = (float)j / sector;
            q = (float)i / stack;
            vertices.push_back(p);
            vertices.push_back(q);
        }
    }
}

void Sphere::generateIndices() {
    int k1, k2;

    for(int i = 0; i < stack; ++i)
    {
        k1 = i * (sector + 1);
        k2 = k1 + sector + 1;

        for (int j = 0; j < sector; ++j, ++k1, ++k2) {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if(i != stack - 1)
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Sphere::loadTexture() {

    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

      unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(texture);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
        exit(-1);
    }
    stbi_image_free(data);
}

void Sphere::bindAttributes() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

