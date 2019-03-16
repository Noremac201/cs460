#include <algorithm>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include "linear_algebra.cpp"
#include <unistd.h>
#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;

const int WINDOW_WIDTH = 1440 / 2;
const int WINDOW_HEIGHT = 900 / 2;

void drawLine2(Point2 v, Point2 u)
{
    glBegin(GL_LINES);
    glVertex2f(v.x, v.y);
    glColor3f(1,0,0);
    glVertex2f(u.x, u.y);
    glColor3f(1,1,1);
    glEnd();
    glFlush();
}

void drawBoundary(std::vector<Point2> pts) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < pts.size(); i++)
    {
        glVertex2f(pts[i].x, pts[i].y);
    }
    glEnd();
    glFlush();
}

double Clip_line(Point2 &a, Point2 &b, Point2 &c, Point2 &d)
{
    if (inner(perp(d-c), b-a) != 0)
    {
        double t = inner(perp(d-c), c-a)/inner(perp(d-c), b-a);
        double u = inner(perp(b-a), c-a)/inner(perp(d-c), b-a);
        // Ignore if t doesn't reach u, since we don't care
        if (t > 0.0001 && u >= 0.0001 && u <= 1)
        {
            b = a + (inner(perp(d-c), c-a)/inner(perp(d-c), b-a)) * (b - a);
            return t;
        }
    }
    return -1;
}

void part1() {
    // Arbitrary Convex Polygon
    std::vector<Point2> p;
    p.push_back(Point2(100, 300));
    p.push_back(Point2(100, 0));
    p.push_back(Point2(450, 100));
    p.push_back(Point2(400, 400));
    drawBoundary(p);

    Point2 a, b;
    // arbitrary points
    a = { 250, 250};
    b = { 40, 120};

    for (int j = 0; j < 1000; j++)
    {
        double minT = 10000;
        Point2 u, v;
        for (int i = 0;	i < p.size(); i++)
        {
            // Edits a and b in method 
            double t = Clip_line(a, b, p[i], p[(1 + i) % p.size()]);

            if (t == -1)
                continue;

            if ( t < minT)
            {
                minT = t;
                u = p[i];
                v = p[(1+i) % p.size()];
            }
        }

        Vector2 rray = b - a;
        Vector2 re = reflect(rray, v-u);
        Point2 zed = Point2(b.x + re.delta_x(), b.y + re.delta_y());
        drawLine2(a, b);

        a = b;
        b = zed;
    }
}

void display()
{
    part1();
}
void init(int *argc, char** argv) {
    glutInit(argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    glutCreateWindow("Graphics"); // Create a window with the given title
    gluOrtho2D(0, 800, 0, 800);  //  specifies the projection matrix
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the event-processing loop
}

int main(int argc, char **argv) {
    init(&argc, argv);
}
