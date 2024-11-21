#pragma once

#include "shader.h"
#include "transform.h"
#include "vertexbufferobject.h"

class Scene {

private:
    unsigned int vao;
    VertexBufferObject* vbo;

private:
    unsigned int shaderProgram;
    Shader* vertexShader;
    Shader* geometryShader;
    Shader* fragmentShader;

private:
    unsigned int uniformMVP;
    Transform* modelTransform;
    Transform* cameraTransform;

public:
    Scene();
    ~Scene();
    void Init();
    void Render();
    void BindVertices(const void *data, const int size);
};