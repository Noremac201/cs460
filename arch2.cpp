#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define window_width 640.0
#define window_height 480.0

void DrawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * M_PI * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
    glFlush();
}

void drawArch(float h, float w) {
    //draw rect
    float x = window_width / 2.0;
    float y = window_height / 2.0;
    DrawRect(x - w, y - (h / 2.0), x + w, y + (0.5 * h));
    DrawCircle(x, y - (h / 2.0), w, 1000);
}

void main_loop_function() {
    drawArch(100, 100);
    glFlush();
    //DrawCircle(0, 0, 1.0, 100.0);
}

void GL_Setup() {
    glClearColor(0.4, 1.0, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.4, 0.4);
    glPointSize(4.0);
    glLoadIdentity();
    gluOrtho2D(0.0, window_width, window_height, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Arches");
    GL_Setup();
    glutDisplayFunc(main_loop_function);
    glutMainLoop();
}
