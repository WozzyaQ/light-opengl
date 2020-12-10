
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

    std::string sphereVertexPath = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.vert";
    std::string sphereFragmentPath = "/home/vladyslav/CLionProjects/opengl_light/res/sphere.frag";

    Shader* sphereShader = new Shader (sphereVertexPath.c_str(), sphereFragmentPath.c_str());

    Sphere* sun = new Sphere(sunTexturePath, sphereShader, 50, 50, 0.5f);
    Sphere* venus = new Sphere(venusTexturePath, sphereShader, 50, 50, 7.0f);

    std::vector<Sphere*> sphereVec;
    sphereVec.push_back(sun);
    sphereVec.push_back(venus);

    Logic* logic = new Logic(sphereVec);
    engine.loadLogic(logic);

    engine.loop();
}