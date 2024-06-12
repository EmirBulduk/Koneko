cmake_minimum_required(VERSION 3.28)
project(koneko)

find_package(glfw3 CONFIG REQUIRED)
find_package(soil2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)
find_package(FTGL CONFIG REQUIRED)

add_executable(koneko main.cpp
        neuralnetwork.cpp
        neuralnetwork.h
        stb/stb_image.h
        LoadingMenu.cpp
        LoadingMenu.h
        common.h
        GameUI.cpp
        GameUI.h
        ConnectionHandler.cpp
        ConnectionHandler.h
        circle.cpp
        circle.h
        arayuz/playersignin.cpp
        arayuz/playersignin.h)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${FREEGLUT_INCLUDE_DIR})
link_directories(${GLEW_LIBRARY_DIRS})

target_link_libraries(koneko PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)
target_link_libraries(koneko PRIVATE ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES})
target_link_libraries(koneko PRIVATE ftgl)
target_link_libraries(koneko PRIVATE soil2)
target_link_libraries(koneko PRIVATE glfw)
