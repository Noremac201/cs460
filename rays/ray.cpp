#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <random>

#include "linear_algebra.cpp"

#define window_width 640.0
#define window_height 480.0


struct Point {
    double x, y;

    void print() {
        printf("Point - {%lf %lf}\n", x, y);
    }

};

struct Line {
    Point p1, p2;
};

struct min_max {
    double xMax;
    double xMin;
    double yMax;
    double yMin;
};

double dotProduct(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
//z is a point on polygon other than on line l
/*
had a lot of trouble in this method - see this carefully
*/
int chopCI(double &tIn, double &tOut, double numer, double denom) {
    double tHit;
    if (denom < 0) {
        tHit = numer / denom;
        if (tHit > tOut)
            return 0;
        else if (tHit > tIn)
            tIn = tHit;
    } else if (denom > 0) {
        tHit = numer / denom;
        if (tHit < tIn)
            return 0;
        if (tHit < tOut)
            tOut = tHit;
    } else {
        if (numer <= 0)
            return 0;
    }
    return 1;
}

int cyrusBeck(std::vector <Line2> poly, Line2 ll) {
    double numer, denom;
    double tIn = 0.0;
    double tOut = 1.0;
    Vector2 c, tmp;
    c = ll.direction();

    for (int i = 0; i < poly.size(); i++) {
        tmp = poly[i].base() - ll.base();
        numer = poly[i].normal() * tmp;
        denom = poly[i].normal() * c;
        //if (!chopCI(tIn, tOut, numer, denom))
        //    return 0;
    }
    if (tOut < 1.0) {
        std::cout << "here" << std::endl;
        //ll..x = ll.p1.x + c.x * tOut;
        //ll.p2.y = ll.p1.y + c.y * tOut;
    }
    if (tIn > 0.0) {
        std::cout << "here 0 " << std::endl;
        //ll.p1.x = ll.p1.x + c.x * tIn;
        //ll.p1.y = ll.p1.y + c.y * tIn;
    }
    glBegin(GL_LINES);
    glVertex2f(ll.base().get_x(), ll.base().get_y());
    glVertex2f(ll.base().get_x() + ll.direction().delta_x(), ll.base().get_y() + ll.direction().delta_y());
    std::cout << ll.printable() << std::endl;
    glEnd();
    glFlush();
    glutSwapBuffers();
    return 1;
}

min_max findMinMax(std::vector <Point> pts) {
    min_max mm;
    mm.xMin, mm.yMin = std::numeric_limits<double>::max();
    mm.xMax, mm.yMax = std::numeric_limits<double>::min();

    for (Point p : pts) {
        double x = p.x;
        double y = p.y;

        if (x > mm.xMax)
            mm.xMax = x;
        else if (x < mm.xMin)
            mm.xMin = x;

        if (y > mm.yMax)
            mm.yMax = y;
        else if (y < mm.yMin)
            mm.yMin = y;
    }
    return mm;
}

double randDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

Point randomStart(std::vector <Point> pts) {
    min_max mm = findMinMax(pts);
    Point p;

    double x = randDouble(mm.xMin, mm.xMax);
    double y = randDouble(mm.yMin, mm.yMax);

    p = {x, y};
    //std::cout << pInPolygon(pts, p) << std::endl;

    return {-200.0, 310.0};
}

void drawBoundary(std::vector <Line2> lines) {
    glBegin(GL_LINE_LOOP);
    for (Line2 line : lines) {
        Point2 base = line.base();
        glVertex2f(base.get_x(), base.get_y());
        std::cout << line.printable() << std::endl;
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void main_loop_function() {
    std::vector <Line2> a;
    Point2 p1(-300.0, 420.0);
    Point2 p2(-200.0, 200.00);
    Point2 p3(300.0, -400.0);
    Point2 p4(300.0, 400.0);
    a.push_back(Line2(p1, p2 - p1));
    a.push_back(Line2(p2, p3 - p2));
    a.push_back(Line2(p3, p4 - p3));
    a.push_back(Line2(p4, p1 - p4));

    gluOrtho2D(-window_width, window_width, window_height, -window_height);
    drawBoundary(a);

    Point2 pa = {250.0, 250.0}; //randomStart(a);
    Point2 pb = {pa.get_x(), pa.get_y() + 1000};
    //Point aa = minimum_distance(a[0], a[1], p);
    Line2 seg(pa, pb - pa);
    cyrusBeck(a, seg);

}

void GL_Setup() {
    glClearColor(0.4, 1.0, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glColor3f(1.0, 0.4, 0.4);
    glPointSize(10.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Ray Tracing");
    GL_Setup();
    glutDisplayFunc(main_loop_function);
    glutMainLoop();
}
