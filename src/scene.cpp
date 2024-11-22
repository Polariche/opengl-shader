
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "scene.h"
#include "utils.h"

Scene::Scene() {

}

void Scene::Init() {
    shaderProgram = glCreateProgram();

    std::string vertexShaderSource = load_text("../src/shaders/vert.vert");
    if (!vertexShaderSource.empty()) {
        vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        vertexShader->Attach(shaderProgram);
        vertexShader->Delete();
    }

    std::string geometryShaderSource = load_text("../src/shaders/geom.geom");
    if (!geometryShaderSource.empty()) {
        geometryShader = new Shader(GL_GEOMETRY_SHADER, geometryShaderSource.c_str());
        geometryShader->Attach(shaderProgram);
        geometryShader->Delete();
    }

    std::string fragmentShaderSource = load_text("../src/shaders/frag.frag");
    if (!fragmentShaderSource.empty()) {
        fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
        fragmentShader->Attach(shaderProgram);
        fragmentShader->Delete();
    }

    glLinkProgram(shaderProgram);
    
    glGenVertexArrays(1, &vao);
    vbo = new VertexBufferObject();

    uniformMVP = glGetUniformLocation(shaderProgram, "mvp");
    modelTransform = new Transform();
    cameraTransform = new Transform();

}

void Scene::BindVertices(const void *data, const int size) {
    this->verticesCount = size / sizeof(float);

    glBindVertexArray(vao);
    
    vbo->BufferData(data, size);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    vbo->Unbind();

    glBindVertexArray(0);
}

void Scene::Render() {
    glUseProgram(shaderProgram);

    glm::mat4 mvp;
    if (!!modelTransform)
        mvp = modelTransform->GetMatrix();
    else
        mvp = glm::mat4(1.0F);
    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vao);
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, verticesCount);
    glBindVertexArray(0);
}

void Scene::ProcessInput(Input* input) {
    const float diff = 3.14f * 0.10f / 60;
    glm::quat rot = modelTransform->GetRotation();
    glm::quat inv = glm::inverse(rot);
    
    glm::quat rot2 = rot * inv;

    // rotation with respect to the world coord
    if (input->GetUp())
        rot = glm::quat(glm::vec3(diff, 0.0f, 0.0f)) * rot;
    
    if (input->GetDown())
        rot = glm::quat(glm::vec3(-diff, 0.0f, 0.0f)) * rot;

    if (input->GetLeft())
        rot = glm::quat(glm::vec3(0.0f, diff, 0.0f)) * rot;

    if (input->GetRight())
        rot = glm::quat(glm::vec3(0.0f, -diff, 0.0f)) * rot;

        
    // // rotation with respect to the local coord
    // if (input->GetUp())
    //     rot = rot * glm::quat(glm::vec3(diff, 0.0f, 0.0f));
    
    // if (input->GetDown())
    //     rot = rot * glm::quat(glm::vec3(-diff, 0.0f, 0.0f));

    // if (input->GetLeft())
    //     rot = rot * glm::quat(glm::vec3(0.0f, diff, 0.0f));

    // if (input->GetRight())
    //     rot = rot * glm::quat(glm::vec3(0.0f, -diff, 0.0f));
    
    modelTransform->SetRotation(rot);
}