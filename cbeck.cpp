#include <iostream>
// Cyrus-Beck 2-D Line Clipping algorithm
// for ease of coding we will treat a 2D point and a 2D vector
// as the same
const int MAXP = 100;
const int MAXN = 100;

struct Point2D
{
    float x, y;

    std::string to_string()
    {
        return "(" + std::to_string(x) + ", " + std::to_string(x) + ")";
    }
};

typedef Point2D Normal[MAXN];
// for simplicity we set an upper bound on the number of
// points allowed to define a polygon - by moving to a class
// with a constructor we could make the array any size we wanted
struct Polygon
{
    int nPoints;
    Point2D v[MAXP];
};

float dotProduct (Point2D v1, Point2D v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// compute the outer normals.
// note that this requires that the polygon be convex
// to always work
void calcNormals (Polygon p, Normal& n)
{
    int j,k;
    Point2D v;
    for (int i = 0; i < p.nPoints; i++)
    {
        j = (i+1) % p.nPoints;
        k = (i+2) % p.nPoints;
        // make vector be -1/mI + 1J
        n[i].x = -(p.v[j].y - p.v[i].y)/(p.v[j].x - p.v[i].x);
        n[i].y = 1.0;
        v.x = p.v[k].x - p.v[i].x;
        v.y = p.v[k].y - p.v[i].y;
        if (dotProduct(n[i],v) > 0)    // inner normal
        {
            n[i].x *= -1;
            n[i].y  = -1;
        }
    }
}

bool cbClip (Point2D p1, Point2D p2, Normal n, Polygon p,
             Point2D & rp, Point2D & q)
{
    /*
     * param p1, p2: These are the points representing the line that should be clipped
     * param p: A list of points that constitute the polygon that will clip the line.
     * param rp, q: Points that will be edited in the method that will end up being the clipped line/points.
     */
    float t1, t2, t, num, den;
    Point2D dirV, F;          // vectors
    int I;

    // start largest at smallest legal value and smallest
    // at largest legal value
    t1 = 0.0;
    t2 = 1.0;
    // compute the direction vector
    dirV.x = p2.x - p1.x;
    dirV.y = p2.y - p1.y;

    bool visible = true;
    int i = 0;
    while ( (i < p.nPoints) && visible)
    {   F.x = p1.x - p.v[i].x;
        F.y = p1.y - p.v[i].y;

        num  = dotProduct (n[i],F);
        den   =  dotProduct (n[i],dirV);

        if (den == 0.0)          // Parallel or Point
        {
            // parallel - if outside then forget the line; if inside then there are no
            // intersections with this side
            // but there may be with other edges, so in this case just keep going
            if (num > 0.0)
                // Parallel and outside or point (p1 == p2) and outside
                visible = false;
        }
        else
        {
            t = -(num/den);
            if (den < 0.0)        // entering
            {
                if (t <= 1.0)
                    if (t > t1)
                        t1 = t;
            }
            else if ( t >= 0.0)    //exiting
                if (t < t2)
                    t2 = t;
        }
        i++;
    }
    if ( t1 <= t2)
    {
        rp.x = p1.x + t1 * dirV.x;
        rp.y = p1.y + t1 * dirV.y;
        q.x = p1.x + t2 * dirV.x;
        q.y = p1.y + t2 * dirV.y;
    }
    else
        visible = false;
    return visible;
}

int main()
{
    // CLipping Polygon
    Point2D p1 = {0, 0};
    Point2D p2 = {0, 100};
    Point2D p3 = {100, 100};
    Point2D p4 = {100, 0};

    // Polygon consiting of points
    Polygon p = {4, {p1, p2, p3, p4}};

    // Point a, "Direction Vector" B
    Point2D a = {50, 50};
    Point2D b = {200, 200};

    // Points that will be passed by reference to cbClip and edited
    // inside that method and returned
    Point2D rp = {0, 0};
    Point2D q = {0, 0};

    Normal n;
    calcNormals(p, n);

    cbClip(a, b, n, p, rp, q);

    std::cout << rp.to_string() << std::endl;
    std::cout << q.to_string() << std::endl;
    return 0;
}
