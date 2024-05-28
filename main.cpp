#include <iostream>
#include <gl/glut.h>
#include <cmath>


struct Point {
    GLint x;
    GLint y;
};

struct GLColor {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

GLColor colors[6] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 1.0f}
};

GLColor color = colors[0];

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0);
    glColor3f(color.red, color.green, color.blue);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

void display(void) {

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
    GLfloat step = 1/radius;
    GLfloat x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);

    for(GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radius * cos(theta));
        y = pC.y + (radius * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

void setupDisplay(Point p1, Point p2) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
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
    Point p = {320, 240};	// draw_pixel
    Point p1 = {10, 100};	// draw_line
    Point p2 = {200, 100};	// --

    Point pC = {600, 450};	// Circle center point
    GLfloat radius = 200;	// Circle radius

    switch(choice) {
        case 1:	// Pixel
            draw_pixel(p);
            break;

        case 2:	// Line
            draw_dda(p1, p2);
            break;

        case 3:	// Circle
            draw_circle(pC, radius);
            break;

        case 4: // Ellipse
            draw_ellipse(pC, 60.0f, 200.0f);
            break;

        case 5:	// Exit
            exit(0);
            break;
    }
}

void importplayer() {
  std::cout << "importing player" << std::endl;
    printf("damn");
}

void exportplayer() {

}



void sbmtwoholder(int secim) {
    Point p1 = {10, 100};	// Line start point
    Point p2 = {200, 100};	// Line end point
    switch (secim) {

        case 1:
            importplayer();
            break;

        case 2:
            setupDisplay(p1, p2);
            break;
    }

}


void subMenuHandler(int choice) {
    color = colors[choice];
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("OpenGL Circle and Menus");
    glutDisplayFunc(display);
    init();

    int subMenu = glutCreateMenu(subMenuHandler);
    glutAddMenuEntry("Default", 0);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Purple", 5);

    int sbmtwo = glutCreateMenu(sbmtwoholder);
    glutAddMenuEntry("import", 1);
    glutAddMenuEntry("export", 2);

    glutCreateMenu(mainMenuHandler);
    glutAddSubMenu("Change Color", subMenu);
    glutAddSubMenu("Player", sbmtwo);
    glutAddMenuEntry("Pixel", 1);
    glutAddMenuEntry("Line", 2);
    glutAddMenuEntry("Circle", 3);
    glutAddMenuEntry("Ellipse", 4);
    glutAddMenuEntry("Exit", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}