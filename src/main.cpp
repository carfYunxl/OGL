#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader/shader.h>
#include <camera/camera.h>
#include <iostream>
#include "../include/GL_init.h"
#include "../include/callBackFunction.h"
#include "../include/texture.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Renderer.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 900;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(0.0f, 0.0f, 5.0f);

int main()
{
    GL_init();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f
    };

    unsigned int indices[]
    {
        0,1,2,
        0,2,3,

        4,5,6,
        4,7,6,

        2,3,6,
        3,6,7,

        0,1,5,
        0,4,5,

        0,3,7,
        0,4,7,

        1,2,6,
        1,5,6
    };

    VertexArray va_cube;
    VertexArray va_light;

    VertexBuffer vb(vertices, 3 * 8 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);

    va_cube.AddBuffer(vb, layout);
    va_light.AddBuffer(vb, layout);

    Shader cubeShader("src/Basic_cube.shader");
    Shader lightShader("src/Basic_light.shader");

    IndexBuffer ib(indices, 36);

    va_cube.UnBind();
    va_light.UnBind();
    vb.UnBind();
    ib.UnBind();

    cubeShader.UnBind();
    lightShader.UnBind();

    // unsigned int tex1 = 0;
    // Texture texture1("res/container.jpg",&tex1);

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window,camera,deltaTime);

        renderer.Clear();

        //glActiveTexture(GL_TEXTURE0);
        //texture1.bind_Tex(tex1);

        //---------- Draw light -----------------------
#if 1
        lightShader.Bind();
        lightShader.setVec3("lightPos", lightPos);
        lightShader.setVec3("viewPos", camera.Position);

        // light properties
        glm::vec3 lightColor{};
        lightColor.x = static_cast<float>(sin(2.0));
        lightColor.y = static_cast<float>(sin(0.7));
        lightColor.z = static_cast<float>(sin(1.3));

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.8f); // low influence
        lightShader.setVec3("light.ambient", ambientColor);
        lightShader.setVec3("light.diffuse", diffuseColor);
        lightShader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);

        // material properties
        lightShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        lightShader.setFloat("material.shininess", 32.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        lightShader.setMat4("model", model);

        model = glm::mat4(1.0f);
        float angle = 0.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 1.0f));
        lightShader.setMat4("model", model);

        renderer.Draw(va_light, ib, lightShader);
#endif
        
#if 1
        cubeShader.Bind();
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.7f));
        cubeShader.setMat4("model", model);
        renderer.Draw(va_cube, ib, cubeShader);
#endif
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}