#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include <iostream>
#include <tchar.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "LoadingMenu.h"

#include "common.h"

GLuint texture;



GLColor colors[7] = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.5f, 0.0f}
};

GLColor color = colors[0];



void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0);
    glColor3f(color.red, color.green, color.blue);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}





void draw_pixel(Point p) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
    glFlush();
}



void draw_dda(Point p1, Point p2) {
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if(abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    GLfloat xInc = dx/step;
    GLfloat yInc = dy/step;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);

    for(float i = 1; i <= step; i++) {
        glVertex2i(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
    glEnd();
    glFlush();

}





void draw_circle(Point pC, GLfloat radius) {
    GLfloat step = 1 / radius;
    GLfloat x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);

    for (GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radius * cos(theta));
        y = pC.y + (radius * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}





void draw_ellipse(Point pC, GLfloat radiusY, GLfloat radiusX) {
    GLfloat step = 1/radiusX;
    GLfloat x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
    for(GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radiusX * cos(theta));
        y = pC.y + (radiusY * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}





void mainMenuHandler(int choice) {
    Point p = {320, 240};
    Point p1 = {10, 100};
    Point p2 = {200, 100};

    Point pC = {600, 450};
    GLfloat radius = 200;

    switch(choice) {
        case 1:
            draw_pixel(p);
            break;

        case 2:
            exit(0);
            break;
    }
}

void importplayer() {
    std::cout << "importing player" << std::endl;
    printf("in proc");
}



void sbmtwoholder(int secim) {
    Point p1 = {400, 0};
    Point p2 = {400, 800};
    switch (secim) {

        case 1:
            importplayer();
            break;

        case 2:
            std::cout << "Empty Function" << std::endl;
            break;
    }
}



void display(void) {

}

void subMenuHandler(int choice) {
    color = colors[choice];
}

void MainSystemHandler(int argc, char** argv) {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("BULDUK");
    glutDisplayFunc(display);
    init();

    int subMenu = glutCreateMenu(subMenuHandler);
    glutAddMenuEntry("Default", 0);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Purple", 5);
    glutAddMenuEntry("Orange", 6);

    int sbmtwo = glutCreateMenu(sbmtwoholder);
    glutAddMenuEntry("import", 1);
    glutAddMenuEntry("SetupDisplay", 2);

    glutCreateMenu(mainMenuHandler);
    glutAddSubMenu("Main", sbmtwo);
    glutAddSubMenu("Change Color", subMenu);
    glutAddMenuEntry("Pixel", 1);
    glutAddMenuEntry("Exit", 2);


    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

}



int main(int argc, char** argv) {


    glutInit(&argc, argv);
    initLoader(argc, argv);
    MainSystemHandler( argc, argv);

    return 0;
}