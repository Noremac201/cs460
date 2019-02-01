#include <GL/glut.h>
#include <iostream>


struct Point {
    int x = 0;
    int y = 0;
};

const int INIT_WINDOW_WIDTH = 640.0;
const int INIT_WINDOW_HEIGHT = 480.0;

Point initPoint = {115, 121};

void gingerInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, INIT_WINDOW_WIDTH, 0.0, INIT_WINDOW_HEIGHT);
}

void drawGinger(Point p, int points) {
    int m = 40, l = 3;
    Point q = {0, 0};
    glBegin(GL_POINTS);
    for (int i = 0; i < points; i++) {
        q.x = m * (1 + 2 * l) - p.y + abs(p.x - l * m);
        q.y = p.x;
        glVertex2i(q.x, q.y);
        p = q;
    }
    glEnd();
    glFlush();
}

void drawGinger(Point p) {
    drawGinger(p, 1000000);
}

void gingerDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawGinger(initPoint);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    // glutInitWindowPosition(0,0);
    glutCreateWindow("Gingerbread Man");
    glutDisplayFunc(gingerDisplay);
    gingerInit();
    glutMainLoop();
}