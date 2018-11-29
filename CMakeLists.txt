cmake_minimum_required(VERSION 3.12)
project(navigation_trash)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 14)



include_directories(.)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(navigation_trash
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/meshes.txt
        cmake-build-debug/Navigation_Mesh
        cmake-build-debug/navigation_mesh
        cmake-build-debug/Navigation_Mesh.cbp
        cmake-build-debug/navigation_mesh.cbp
        cmake-build-debug/untitled
        cmake-build-debug/untitled.cbp
        CMakeLists.txt
        DStar.cpp
        DStar.h
        main.cpp
        NavMesh.cpp
        NavMesh.h
        Scene.cpp
        Scene.h)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})