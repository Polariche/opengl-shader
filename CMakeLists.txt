cmake_minimum_required(VERSION 3.16.3)
project(shader2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW 2.1 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(shader2
        src/main.cpp
)
target_link_libraries(shader2
        glfw
        OpenGL
        GLEW
        glm::glm
)