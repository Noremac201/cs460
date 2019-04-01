#include <GL/glut.h>
#include <GL/glu.h>
#include <algorithm>

const int WINDOW_WIDTH = 1440 / 2;
const int WINDOW_HEIGHT = 900 / 2;

void setPixel(int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void bresenham(int ax, int ay, int bx, int by) {
    if (ax >= bx) 
    {
        std::swap(ax, bx);
        std::swap(ay, by); 
    }

    int W = bx- ax;
    int H = by - ay;

    int x = ax;
    int y = ay;

    setPixel(x, y);

    int p = 2 * H - W;
    // iterate until right of end x 
    while (x < bx) 
    {
        if (p < 0)
        {
            p += (2 * H);
        }
        else 
        {
            p += (2 * (H - W));
            y++;
        }
        setPixel(++x, y);
    }
}

void display()
{
    bresenham(100, 100, 200, 200);
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
