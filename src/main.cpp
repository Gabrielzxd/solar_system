#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../include/CelestialBody.h"
#include <cmath>
#include "../include/stb_image.h"

int main() {
    glfwInit();

    GLFWmonitor* primary = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Simulação Sistema Solar", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float aspectRatio = (float)mode->width / (float)mode->height;

    std::vector<CelestialBody> bodies;
    bodies.emplace_back("Sol", Vec2{0.0, 0.0}, Vec2{0.0, 0.0}, 1.0, 0.8, Color{1.0f, 0.9f, 0.0f});
    bodies.emplace_back("Mercurio", Vec2{0.387, 0.0}, Vec2{0.0, 10.09}, 1.65e-7, 0.1, Color{0.6f, 0.6f, 0.6f});
    bodies.emplace_back("Venus", Vec2{0.723, 0.0}, Vec2{0.0, 7.39}, 2.45e-6, 0.2, Color{0.9f, 0.8f, 0.6f});
    bodies.emplace_back("Terra", Vec2{1.000, 0.0}, Vec2{0.0, 6.28}, 3.00e-6, 0.2, Color{0.2f, 0.4f, 1.0f});
    bodies.emplace_back("Marte", Vec2{1.524, 0.0}, Vec2{0.0, 5.08}, 3.23e-7, 0.15, Color{0.9f, 0.3f, 0.1f});
    bodies.emplace_back("Jupiter", Vec2{5.204, 0.0}, Vec2{0.0, 2.75}, 9.54e-4, 0.5, Color{0.8f, 0.6f, 0.4f});
    bodies.emplace_back("Saturno", Vec2{9.582, 0.0}, Vec2{0.0, 2.05}, 2.85e-4, 0.4, Color{0.9f, 0.8f, 0.5f});
    bodies.emplace_back("Urano", Vec2{19.201, 0.0}, Vec2{0.0, 1.43}, 4.36e-5, 0.3, Color{0.6, 0.9f, 0.9f});
    bodies.emplace_back("Netuno", Vec2{30.047, 0.0}, Vec2{0.0, 1.14}, 5.15e-5, 0.3, Color{0.2f, 0.3f, 0.9f});

    double dt = 0.01;
    float zoom = 40.0f;

    while (!glfwWindowShouldClose(window)) {
        for(size_t i = 0; i < bodies.size(); i++) {
            for(size_t j = 0; j < bodies.size(); j++) {
                if(i != j) bodies[i].attract(bodies[j]);
            }
        }
        for (auto& body : bodies) body.update(dt);

        // --- RENDERIZACAO ---
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f); // Fundo quase preto
        glClear(GL_COLOR_BUFFER_BIT);

        Vec2 sunPos = bodies[0].getPosition();

        // Desenhar os corpos
        glPointSize(10.0f);
        float visual_scale = 0.03f;
        for (const auto& body : bodies) {
            Vec2 p = body.getPosition();
            Color colors = body.getColor();
            glColor3f(colors.r, colors.g, colors.b);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 60; i++){
                float theta = 2.0f * 3.1415926f * i / 60.0f;
                float x = body.getRadius() * cos(theta) * visual_scale;
                float y = body.getRadius() * sin(theta) * visual_scale;
                glVertex2f( (((p[0] - sunPos[0]) / zoom) + x) / aspectRatio, ((p[1] - sunPos[1]) / zoom) + y );
            }
            glEnd();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}