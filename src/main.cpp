// main.cpp gerado com Gemini para testar a nova física do projeto.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

#include "../include/CelestialBody.h"
#include "../include/stb_image.h"
#include "../include/json.hpp"
#include "../include/physics.h" // Apenas o cabeçalho

using json = nlohmann::json;

int main() {
    glfwInit();
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Simulação Sistema Solar", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float aspectRatio = (float)mode->width / (float)mode->height;

    // --- 1. PREPARAÇÃO DOS DADOS E DA FÍSICA ---
    std::vector<CelestialBody> bodies;
    std::vector<double> masses;
    State estado_atual;

    std::ifstream arquivo_json("bodies.json");
    if (!arquivo_json.is_open()) {
        std::cerr << "Erro ao abrir o arquivo planetas.json!\n";
        return -1;
    }

    json dados;
    arquivo_json >> dados;

    for (const auto& item : dados["corpos_celestes"]) {
        std::string nome = item["nome"];
        
        // Lendo os vetores 3D do JSON
        linalg::Vector<3> pos = { item["posicao"][0], item["posicao"][1], item["posicao"][2] };
        linalg::Vector<3> vel = { item["velocidade"][0], item["velocidade"][1], item["velocidade"][2] };
        
        double massa = item["massa"];
        double raio = item["raio"];
        Color cor = { item["cor"][0], item["cor"][1], item["cor"][2] };

        // Preenche o objeto visual
        bodies.emplace_back(nome, pos, vel, massa, raio, cor);
        
        // Preenche as estruturas puras da física
        masses.push_back(massa);
        estado_atual.pos.push_back(pos);
        estado_atual.vel.push_back(vel);
    }

    double dt = 0.01;
    float zoom = 40.0f;

    // --- 2. LOOP PRINCIPAL ---
    while (!glfwWindowShouldClose(window)) {
        
        // Passo da Física RK4 (Avança o tempo)
        stepRK4(estado_atual, masses, dt);

        // Atualiza a posição nos objetos para que o OpenGL saiba onde desenhar
        for(size_t i = 0; i < bodies.size(); i++) {
            bodies[i].setPosition(estado_atual.pos[i]);
        }

        // --- RENDERIZAÇÃO ---
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        linalg::Vector<3> sunPos = bodies[0].getPosition();

        glPointSize(10.0f);
        float visual_scale = 0.03f;
        
        for (const auto& body : bodies) {
            linalg::Vector<3> p = body.getPosition();
            Color colors = body.getColor();
            
            glColor3f(colors.r, colors.g, colors.b);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 60; i++){
                float theta = 2.0f * 3.1415926f * i / 60.0f;
                float x = body.getRadius() * cos(theta) * visual_scale;
                float y = body.getRadius() * sin(theta) * visual_scale;
                
                // Extraindo X (p[0]) e Y (p[1]) do vetor 3D para renderizar no plano 2D atual
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