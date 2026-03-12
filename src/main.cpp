#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../include/CelestialBody.h"

int main() {
    // 1. Setup Inicial do OpenGL (Igual ao anterior)
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 800, "Simulacao N-Corpos", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 2. Criar os corpos (Sua física)
    std::vector<CelestialBody> bodies;
    bodies.emplace_back(Vector{0.0, 0.0}, Vector{0.0, 0.0}, 100.0, 1.0); // Sol
    bodies.emplace_back(Vector{10.0, 0.0}, Vector{0.0, 3.16}, 1.0, 0.1); // Terra

    double dt = 0.01;
    float zoom = 15.0f; // Fator para caber na tela

    while (!glfwWindowShouldClose(window)) {
        // --- LOGICA DE FISICA ---
        for(size_t i = 0; i < bodies.size(); i++) {
            for(size_t j = 0; j < bodies.size(); j++) {
                if(i != j) bodies[i].attract(bodies[j]);
            }
        }
        for (auto& body : bodies) body.update(dt);

        // --- RENDERIZACAO ---
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f); // Fundo quase preto
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenhar os corpos como pontos grandes (depois faremos circulos)
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        for (const auto& body : bodies) {
            Vector p = body.getPosition();
            // Convertendo a posicao da fisica para a escala do OpenGL (-1 a 1)
            glVertex2f(p.x / zoom, p.y / zoom);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}