
#define GLEW_STATIC 

#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <glm/glm.hpp>

#include<sstream>

#define ASSERT(x) if (!(x)) __builtin_trap(); 
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

float x = 0.0f;
float y = 0.0f;

bool W, A, S, D;

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL_Error] (" << error << "): " << function << 
                    " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

std::optional<std::string> load_text(const char* path) {
    std::ifstream file_steam(path);

    if (!file_steam.is_open()) {
        printf("ERROR OPENING FILE! %s\n", path);
        return std::nullopt;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file_steam)),
        std::istreambuf_iterator<char>()
    );

    return std::make_optional<>(content);
}

void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }
    bool is_down = action == GLFW_PRESS;
    switch (key) {
    case GLFW_KEY_W:
        W = is_down;
        break;
    case GLFW_KEY_A:
        A = is_down;
        break;
    case GLFW_KEY_S:
        S = is_down;
        break;
    case GLFW_KEY_D:
        D = is_down;
        break;
    }

}

void print_shader_error(uint32_t id) {
    int32_t log_length = 0;
    char log[1024];

    glGetShaderInfoLog(id, 1024, &log_length, log);
    std::cout << log << "\n";
}

void print_program_error(uint32_t id) {
    int32_t log_length = 0;
    char log[1024];

    glGetProgramInfoLog(id, 1024, &log_length, log);
    std::cout << log << "\n";
}

int create_program(const std::string& vertex_shader, const std::string& fragment_shader) {
    uint32_t program_id = glCreateProgram();

    uint32_t vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    int32_t result = 0;

    const char* vs_source = vertex_shader.c_str();
    GLint vs_length = vertex_shader.length();

    const char* fs_source = fragment_shader.c_str();
    GLint fs_length = fragment_shader.length();

    glShaderSource(vertex_shader_id, 1, &vs_source, &vs_length);
    glCompileShader(vertex_shader_id);
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if (result != true)
        print_shader_error(vertex_shader_id);

    glShaderSource(fragment_shader_id, 1, &fs_source, &fs_length);
    glCompileShader(fragment_shader_id);
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if (result != true)
        print_shader_error(fragment_shader_id);

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result != true)
        print_program_error(program_id);

    glValidateProgram(program_id);
    glGetProgramiv(program_id, GL_VALIDATE_STATUS, &result);
    if (result != true)
        print_program_error(program_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, &on_key);

    GLenum result = glewInit();
    if (result != GLEW_OK) {
        auto s = glewGetErrorString(result);
        std::cout << s << "\n";
    }
    else {
        std::cout << "Ok" << "\n";
    }

    std::string vertex_source;
    std::string fragment_source;

    if (auto loaded = load_text("../src/vertex.vert")) {
        vertex_source = loaded.value();
    }
    else {
        return -1;
    }
    if (auto loaded = load_text("../src/frag.frag")) {
        fragment_source = loaded.value();
    }
    else {
        return -1;
    }

    uint32_t program = create_program(vertex_source, fragment_source);
    glUseProgram(program);

    int32_t camera_position = glGetUniformLocation(program, "camera_position");
    int32_t obj_color = glGetUniformLocation(program, "obj_color");
    int32_t cur_time = glGetUniformLocation(program, "cur_time");

    float vertices[8] = {
            0.8F, 0.8F,
            -0.8F, 0.8F,
            -0.8F, -0.8F,
            0.8F, -0.8F
    };

    uint32_t indices[6] = {
            0, 1, 2, 0, 2, 3
    };

    uint32_t vertex_buffer = 0;
    GLCall(glGenBuffers(1, &vertex_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW));

    uint32_t index_buffer = 0;
    GLCall(glGenBuffers(1, &index_buffer));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glUniform2f(camera_position, x, y));
        GLCall(glUniform4f(obj_color, 1.0f, 0.0f, 1.0f, 1.0f));
        GLCall(glUniform1f(cur_time, (float) glfwGetTime()));

        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());
        if (W)
            y += 0.1;
        if (A)
            x -= 0.1;
        if (S)
            y -= 0.1;
        if (D)
            x += 0.1;
        

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}