
#define GLEW_STATIC 

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "scene.h"
#include "shader.h"
#include "vertexbufferobject.h"



int main () 
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(640, 480, "Hello Cubes", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLenum result = glewInit();

    Scene* scene = new Scene();
    scene->Init();
    
    // const int N = 2;
    // float vertices[N*N*N*3];
    // for (int i=0;i<N;i++) {
    //     for (int j=0;j<N;j++) {
    //         for (int k=0;k<N;k++) {
    //             vertices[i*(3*N*N)+j*(3*N)+k*3 + 0] = (float) k / N * 0.8F;
    //             vertices[i*(3*N*N)+j*(3*N)+k*3 + 1] = (float) j / N * 0.8F;
    //             vertices[i*(3*N*N)+j*(3*N)+k*3 + 2] = (float) i / N * 0.8F;
    //         }
    //     }
    // }

    float vertices[] =
    {
        0.0F, 0.4F, 0.0F,
        -0.8F, -0.4F, 0.0F,
        0.8F, -0.4F, 0.0F,
    };
    scene->BindVertices(vertices, (3*3) * sizeof(float));

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        scene->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}