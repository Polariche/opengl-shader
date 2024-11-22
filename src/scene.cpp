
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "scene.h"


// Shaders
const GLchar* vertexShader_source = "#version 330 core\n"
    "#extension GL_ARB_explicit_uniform_location : require\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "}\0";
const GLchar* geometryShader_source = "#version 330 core\n"
    "layout (points) in;\n"
    "layout (triangle_strip, max_vertices = 5) out;\n"
    "uniform mat4 mvp;\n"
    "void build_house(vec4 position)\n"
    "{    \n"
    "   gl_Position = mvp*(position + vec4(-0.2, -0.2, 0.0, 0.0));\n"
    "    EmitVertex();   \n"
    "   gl_Position = mvp*(position + vec4(0.2, -0.2, 0.0, 0.0));\n"
    "    EmitVertex();   \n"
    "   gl_Position = mvp*(position + vec4(-0.2, 0.2, 0.0, 0.0));\n"
    "    EmitVertex();   \n"
    "   gl_Position = mvp*(position + vec4(0.2, 0.2, 0.0, 0.0));\n"
    "    EmitVertex();   \n"
    "   gl_Position = mvp*(position + vec4(0.0, 0.4, 0.0, 0.0));\n"
    "    EmitVertex();   \n"
    "   EndPrimitive();\n"
    "}\n"
    "void main() {    \n"
    "    build_house(gl_in[0].gl_Position);\n"
    "}\0";
const GLchar* fragmentShader_source = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(0.8F, 0.5f, 0.2f, 0.8F);\n"
    "}\n\0";


Scene::Scene() {

}

void Scene::Init() {
    shaderProgram = glCreateProgram();

    vertexShader = new Shader(GL_VERTEX_SHADER, vertexShader_source);
    vertexShader->Attach(shaderProgram);
    vertexShader->Delete();

    
    geometryShader = new Shader(GL_GEOMETRY_SHADER, geometryShader_source);
    geometryShader->Attach(shaderProgram);
    geometryShader->Delete();

    fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShader_source);
    fragmentShader->Attach(shaderProgram);
    fragmentShader->Delete();

    glLinkProgram(shaderProgram);
    
    glGenVertexArrays(1, &vao);
    vbo = new VertexBufferObject();

    uniformMVP = glGetUniformLocation(shaderProgram, "mvp");
    modelTransform = new Transform();
    cameraTransform = new Transform();

}

void Scene::BindVertices(const void *data, const int size) {
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
    if (!!modelTransform) {
        //modelTransform->SetRotation(glm::vec3(0.0f, 3.14f * glfwGetTime(), 0.0f));
        mvp = modelTransform->GetMatrix();
    }
        
    else
        mvp = glm::mat4(1.0F);
    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vao);
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, 3);
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
    //     rot = rot * glm::quat(glm::vec3(diff, 0.0f, 0.0f))t;
    
    // if (input->GetDown())
    //     rot = rot * glm::quat(glm::vec3(-diff, 0.0f, 0.0f));

    // if (input->GetLeft())
    //     rot = rot * glm::quat(glm::vec3(0.0f, diff, 0.0f));

    // if (input->GetRight())
    //     rot = rot * glm::quat(glm::vec3(0.0f, -diff, 0.0f));
    
    modelTransform->SetRotation(rot);
}