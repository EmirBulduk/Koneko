//
// Created by buldu on 5.06.2024.
//

#include <gl/glew.h>
#include <GL/freeglut_std.h>
#include "ButtonSystem.h"
#include "common.h"


void getMousePos(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point mousePos = {x, y};
        for (int i = 0; i < 7; i++) {
            if (mousePos.x >= 0 && mousePos.x <= 100 && mousePos.y >= 0 && mousePos.y <= 100) {
                color = colors[i];
            }
        }
    }
}




void ButtonSystem::initButtons() {
    glutMouseFunc(getMousePos);

}

