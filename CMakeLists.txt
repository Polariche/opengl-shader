cmake_minimum_required(VERSION 3.16.3)
project(shader2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW 2.1 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(shader2
        src/scene.cpp
        src/shader.cpp
        src/vertexbufferobject.cpp
        src/transform.cpp
        src/input.cpp
        src/main.cpp
)

target_link_libraries(shader2
        glfw
        OpenGL
        GLEW
        glm::glm
)

target_include_directories(shader2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_directories(shader2 PRIVATE /usr/lib/x86_64-linux-gnu)
# target_link_libraries(shader2 OpenGL::GL /usr/lib/x86_64-linux-gnu/libglut.so)