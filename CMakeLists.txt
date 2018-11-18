cmake_minimum_required(VERSION 3.12)
project(untitled)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp NavMesh.cpp NavMesh.h Scene.cpp Scene.h)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})