cmake_minimum_required(VERSION 3.28)
project(koneko)

find_package(FreeGLUT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(koneko main.cpp
        neuralnetwork.cpp
        neuralnetwork.h)

target_link_libraries(koneko PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)
target_link_libraries(koneko PRIVATE ${GLUT_LIBRARY} ${OPENGL_LIBRARY})