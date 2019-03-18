#include <algorithm>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include "linear_algebra.cpp"
#include <unistd.h>
#include <cstdlib>
#include <vector>

const int WINDOW_WIDTH = 1440 / 2;
const int WINDOW_HEIGHT = 900 / 2;

int i = 0;
float r = 0;
float g = 0;
float b = 0;

struct Line {
    Point2 a;
    Point2 b;
};

void resetColor()
{
    r = g = b = 0 ;
    i = 1;
}

void incrementColor()
{
    r = (i >> 16) & 0xFF;
    g = (i >> 8) & 0xFF;
    b = (i) & 0xFF;

    i = i + (255*255*255 / 1000);
}

void drawLine2(Point2 v, Point2 u)
{
    glBegin(GL_LINES);
    glVertex2f(v.x, v.y);
    glColor3ub(r,g,b);
    glVertex2f(u.x, u.y);
    glEnd();
    glFlush();
    incrementColor();
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

std::vector<Point2> drawCircle(float cx, float cy, float r, int num_segments) 
{ 
    std::vector<Point2> pts;
	float theta = 2 * 3.1415926 / float(num_segments); 
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 
	
	float x = r;//we start at angle = 0 

	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        pts.push_back(Point2(x + cx, y + cy));

        
		//calculate the tangential vector 
		//remember, the radial vector is (x, y) 
		//to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y; 
		float ty = x; 
        
		//add the tangential vector 

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 
        
		//correct using the radial factor 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
    return pts;
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

std::vector<Line> getLines(std::vector<std::vector<Point2>> polys) {
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

void rayBouncer(Point2 a, Point2 b, std::vector<Line> lines)
{
    for (int j = 0; j < 1000; j++)
    {
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
        Vector2 rray = b - a;
        Vector2 re = reflect(rray, u-v);
        Point2 zed = Point2(b.x + re.delta_x(), b.y + re.delta_y());
        drawLine2(a, b);

        a = b;
        b = zed;
    }
}

void part1() {
    // Arbitrary Convex Polygon
    std::vector<Point2> p;
    p.push_back(Point2(100, 300));
    p.push_back(Point2(100, 0));
    p.push_back(Point2(450, 100));
    p.push_back(Point2(400, 265));
    drawBoundary(p);

    std::vector<std::vector<Point2>> aa;
    aa.push_back(p);

    Point2 a, b;

    // arbitrary points
    a = { 250, 250};
    b = { 40, 135};

    rayBouncer(a, b, getLines(aa));
}

void part2()
{
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

    std::vector<Point2> pIn2;
    pIn2.push_back(Point2(350, 140));
    pIn2.push_back(Point2(400, 150));
    pIn2.push_back(Point2(400, 200));
    pIn2.push_back(Point2(350, 160));
    drawBoundary(pIn2);

    std::vector<Point2> pIn3;
    pIn3.push_back(Point2(225, 140));
    pIn3.push_back(Point2(300, 125));
    pIn3.push_back(Point2(310, 150));
    pIn3.push_back(Point2(290, 300));
    drawBoundary(pIn3);

    std::vector<std::vector<Point2>> aa;
    aa.push_back(p);
    aa.push_back(pIn);
    aa.push_back(pIn2);
    aa.push_back(pIn3);

    Point2 a, b;
    a = { 250, 250};
    b = { 40, 135};

    rayBouncer(a, b, getLines(aa));
}

void part3()
{
    // Arbitrary Convex Polygon
    std::vector<Point2> p;
    p.push_back(Point2(100, 300));
    p.push_back(Point2(100, 0));
    p.push_back(Point2(450, 100));
    p.push_back(Point2(400, 400));
    drawBoundary(p);

    std::vector<std::vector<Point2>> aa;

    std::vector<Point2> cr = drawCircle(300, 275, 50, 300);
    std::vector<Point2> cr1 = drawCircle(125, 175, 24, 300);
    std::vector<Point2> cr2 = drawCircle(410, 140, 14, 300);
    std::vector<Point2> cr3 = drawCircle(200, 75, 65, 300);

    aa.push_back(p);
    aa.push_back(cr);
    aa.push_back(cr1);
    aa.push_back(cr2);
    aa.push_back(cr3);

    Point2 a, b;
    // arbitrary points
    a = { 250, 250};
    b = { 40, 135};

    rayBouncer(a, b, getLines(aa));
}

void display()
{
    part1();
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    resetColor();
    part2();
    getchar();
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    resetColor();
    part3();
    getchar();
    glutSwapBuffers();
}

void init(int *argc, char** argv) {
    glutInit(argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
