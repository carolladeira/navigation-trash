cmake_minimum_required(VERSION 3.12)
project(Navigation_Mesh)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(Navigation_Mesh
        main.cpp
        NavMesh.cpp
        NavMesh.h
        Scene.cpp
        Scene.h DStar.cpp DStar.h)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
