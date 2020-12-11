//
// Created by vladyslav on 9.12.2020.
//
#include "engine.h"

int main()
{
    int windowWidth = 1366;
    int windowHeight = 720;
    std::string title = "Primitive Solar System";
    Camera camera = Camera(glm::vec3(0.0f, 30.0f, 30.0f));


    Engine engine = Engine(title, &camera, windowWidth, windowHeight);
    engine.init();

    std::string sunTexturePath = "/home/vladyslav/CLionProjects/opengl_light/res/sun.jpg";
    std::string venusTexturePath = "/home/vladyslav/CLionProjects/opengl_light/res/venus.jpg";

//    std::string sphereVertexPath = "/home/vladyslav/CLionProjects/opengl_light/res/light.vert";
//    std::string sphereFragmentPath = "/home/vladyslav/CLionProjects/opengl_light/res/light.frag";

//    std::string sphereVertexPath = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.vert";
//    std::string sphereFragmentPath = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.frag";

    std::string sunVertexPath = "/home/vladyslav/CLionProjects/opengl_light/res/sun.vert";
    std::string sunFragmentPath = "/home/vladyslav/CLionProjects/opengl_light/res/sun.frag";

    std::string venusVertexPath = "/home/vladyslav/CLionProjects/opengl_light/res/venus.vert";
    std::string venusFragmentPath = "/home/vladyslav/CLionProjects/opengl_light/res/venus.frag";

    Shader* sunShader = new Shader(sunVertexPath.c_str(), sunFragmentPath.c_str());
    Shader* venusShader = new Shader(venusVertexPath.c_str(), venusFragmentPath.c_str());



    Sphere* sun = new Sphere(sunTexturePath, sunShader, 50, 50, 7.0f);
    Sphere* venus = new Sphere(venusTexturePath, venusShader, 50, 50, 0.5f);

    std::vector<Sphere*> sphereVec;
    sphereVec.push_back(sun);
    sphereVec.push_back(venus);


    Logic* logic = new Logic(sphereVec);
    engine.loadLogic(logic);

    engine.loop();
}