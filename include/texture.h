#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Texture {
public:
	Texture(const char* imagePath,unsigned int* tex) :m_texture(tex) {
        initTexture(imagePath,tex);
	}

    void bind_Tex(unsigned int tex) {
        glBindTexture(GL_TEXTURE_2D, tex);
    }
private:
	unsigned int* m_texture;

    void initTexture(const char* imagePath, unsigned int* tex) {
        glGenTextures(1, tex);
        glBindTexture(GL_TEXTURE_2D, *tex);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
};
#endif //TEXTURE_H