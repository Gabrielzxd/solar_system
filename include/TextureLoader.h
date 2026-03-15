
// TESTE COM CÓDIGO GERADO PELO GEMINI

#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>
#include <string>

inline GLuint loadTexture(const std::string& path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurações de quebra automática (wrapping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Configurações de filtragem (vital para os planetas não ficarem pixelados ao afastar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Inverte o eixo Y para alinhar com o padrão matemático do OpenGL
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    // O último parâmetro 0 diz para manter os canais originais (RGB ou RGBA)
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    if (data) {
        // Verifica se a imagem tem canal Alpha (transparência)
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        
        // Envia a matriz de bytes da RAM (CPU) para a VRAM (GPU)
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Falha ao carregar textura no caminho: " << path << std::endl;
    }
    
    // Libera a memória da CPU, pois os dados já estão na placa de vídeo
    stbi_image_free(data);

    return textureID;
}