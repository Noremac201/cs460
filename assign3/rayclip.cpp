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

struct Line {
    Point2 a;
    Point2 b;
};

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

double Clip_line(const Point2& a, const Point2& b, const Point2 &c, const Point2 &d)
{
    if (inner(perp(d-c), b-a) >= 0 + EPSILON ||
            inner(perp(d-c), b-a) <= 0 - EPSILON)
    {
        double t = inner(perp(d-c), c-a)/inner(perp(d-c), b-a);
        double u = inner(perp(b-a), c-a)/inner(perp(d-c), b-a);
        // Ignore if t doesn't reach u, since we don't care
        if (t > 0.0001 && u >= 0.0000001 && u <= 1.0005)
        {
            return t;
        }
    }
    return -100000;
}

std::vector<Line> getLines(std::vector<std::vector<Point2>> polys)
{
    std::vector<Line> lines;
    for (std::vector<Point2> poly : polys)
    {
        for (int i = 0; i < poly.size(); i++)
        {
            if (i + 1 == poly.size())
                lines.push_back(Line{poly[i], poly[0]});
            else
                lines.push_back(Line{poly[i], poly[i+1]});
        }
    }
    return lines;

}

void part1() {
    // Arbitrary Convex Polygon
    std::vector<Point2> p;
    p.push_back(Point2(100, 300));
    p.push_back(Point2(100, 0));
    p.push_back(Point2(450, 100));
    p.push_back(Point2(400, 400));
    drawBoundary(p);

    std::vector<Point2> pIn;
    pIn.push_back(Point2(150, 140));
    pIn.push_back(Point2(200, 150));
    pIn.push_back(Point2(200, 200));
    pIn.push_back(Point2(150, 200));
    drawBoundary(pIn);

    std::vector<std::vector<Point2>> aa;
    aa.push_back(p);
    aa.push_back(pIn);
    std::vector<Line> lines = getLines(aa);

    Point2 a, b;
    // arbitrary points
    a = { 250, 250};
    b = { 40, 135};

    for (int j = 0; j < 1000; j++)
    {
        cout << "Iteration" << endl;
        double minT = 10000;
        Point2 u, v;


        Point2 newB;
        for (Line line : lines)
        {
            Point2 p1 = line.a;
            Point2 p2 = line.b;
            // Edits a and b in method 
            double t = Clip_line(a, b, p1, p2);

            if (t == -100000)
                continue;

            if ( t < minT)
            {
                minT = t;
                u = p1;
                v = p2;
                newB  = a + (inner(perp(p2-p1), p1-a)/inner(perp(p2-p1), b-a)) * (b - a);
            }
        }
        
        b = newB;
        cout << "Selected: " << u.printable() << v.printable() << endl;
        Vector2 rray = b - a;
        Vector2 re = reflect(rray, u-v);
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
