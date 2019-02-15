#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define window_width 640.0
#define window_height 480.0

void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y2);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

void drawArc(float cx, float cy, float r, float arc_start, float arc_len)
{
    // Draw counter-clockwise instead of clockwise
    arc_start = 2.0 * M_PI - arc_start;
    glBegin(GL_LINE_STRIP);
    for(int ii = 0; ii < 1000; ii++)
    {
        float theta = 2.0 * M_PI - (arc_len * float(ii) / float(1000));
        theta = theta + arc_start;

        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
    glFlush();
}

void drawRoman(float blx, float bly, float h, float w) {
    //draw rect
    drawRect(blx, bly, blx + 2 * w, bly - h);
    // .05 is to close the circle
    drawArc(blx + w, bly - h, w, 0, M_PI + .05);
}

void drawPointed(float blx, float bly, float h, float w)
{
    drawRect(blx, bly, blx + 2 * w, bly - h);
    drawArc(blx, bly - h, 2 * w, 0, M_PI / 3);
    drawArc(blx + 2.0 * w, bly - h, 2 * w, M_PI, -M_PI / 3);
}

void drawOgee(float blx, float bly, float h, float w) {
    drawRect(blx, bly, blx + 2 * w, bly - h);

    drawArc(blx + w, bly - h, w, M_PI, -M_PI / 3.0);
    drawArc(blx + w, bly - h, w, 0, M_PI / 3.0);

    drawArc(blx, bly - h - (sqrt(3.0) * w), w, 5.0 * M_PI / 3.0, M_PI / 3.0);
    drawArc(blx + 2.0 * w, bly - h - (sqrt(3.0) * w), w, M_PI, M_PI / 3.0);
}

void drawCatenary(float x, float y, float a, float b)
{
    glBegin(GL_LINE_STRIP);
    for (int i = -299.2239; i < 299.2239; i++)
    {
        float result = 693.8597 - 68.7672 * cosh(.0100333 * i);
        //float result = a * cosh(i * x) + y;
        glVertex2f(i + x, y - result);
    }
    glEnd();
    glFlush();
}

void drawRoman(float blx, float bly)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    drawRoman(blx, bly, 320, 320);
    drawRoman(blx + 40, bly, 320, 280);
    glutSwapBuffers();
}

void drawPointed(float blx, float bly)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    drawPointed(blx, bly, 320, 320);
    drawPointed(blx + 40, bly, 320, 280);
    glutSwapBuffers();
}

void drawOgee(float blx, float bly)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    drawOgee(blx, bly, 320, 320);
    drawOgee(blx + 60, bly, 320, 260);
    glutSwapBuffers();
}

void drawCatenary(float blx, float bly)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    drawCatenary(blx, bly, 1.5, .5);
    glutSwapBuffers();
}

void main_loop_function() { 
    float blx = -320;
    float bly = 470;

    gluOrtho2D(-window_width, window_width, window_height, -window_height);
    drawRoman(blx, bly);
    getchar();

    drawPointed(blx, bly);
    getchar();

    drawOgee(blx, bly);
    getchar();

    drawCatenary(0, window_height / 2);
    getchar();
}

void GL_Setup() {
    glClearColor(0.4, 1.0, 0.4, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glColor3f(1.0, 0.4, 0.4);
    glPointSize(2.0);
    glLineWidth(2.0);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Arches");
    GL_Setup();
    glutDisplayFunc(main_loop_function);
    glutMainLoop();
}
