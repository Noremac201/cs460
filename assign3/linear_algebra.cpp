// linear_algebra.cpp
#include <cmath>
#include "linear_algebra.h"

using namespace std;

const double PI = 4.0 * atan(1.0);    // causes warning
const GLfloat PIf = static_cast<GLfloat>(PI);
const GLfloat EPSILON = 0.0001f;  // experimentally determined; adjust if needed

Point2::Point2()
{
  x = 0.0f; //constructor 1
  y = 0.0f;
}

Point2::Point2(GLfloat xx, GLfloat yy)
{
  x = xx;  //constructor 2
  y = yy;
}

void Point2::set  (GLfloat xx, GLfloat yy)
{
  x = xx;
  y = yy;
}

// make a printable representation.
string Point2::printable()
{
  return  "(" + to_string(x) + ", " + to_string(y) + ")";
}

void  Point2:: draw(void)
{
  glBegin(GL_POINTS);  //draw this point
  glVertex2f(x, y);
  glEnd();
  glFlush();
}

Vector2::Vector2()
{
  dx = 0.0;  //  constructors
  dy = 0.0;
}

Vector2::Vector2(GLfloat x, GLfloat y)
{
  dx = x;
  dy = y;
}

  // creates a unit vector in direction angle
  // anticlockwise from right
  Vector2::Vector2(GLfloat angle)
  {
    double d_angle = static_cast<double> (angle);
    dx = static_cast<float>(cos(d_angle));
    dy = static_cast<float>(sin(d_angle));
  }

void Vector2::set (GLfloat x, GLfloat y)
{
  dx = x;
  dy = y;
}
GLfloat Vector2::length(void)
{
  return sqrt(dx * dx + dy * dy);
}

GLfloat Vector2::delta_x(void)    // return components
{
  return dx;
}

GLfloat Vector2::delta_y(void)
{
  return dy;
}

string Vector2::printable(void)
{
  return "<" + to_string(dx) + ", " + to_string(dy) + ">";
}

bool operator== (Point2 a, Point2 b)
{
    float EPS = .0001;
    return a.x < b.x + EPS && a.x > b.x - EPS
        && a.y < b.y + EPS && a.y > b.y - EPS;
}

Vector2 operator+ (Vector2 u, Vector2 v)  //  overloaded +
{
  GLfloat x;
  GLfloat y;
  Vector2 temp;
  x = u.delta_x() + v.delta_x();
  y = u.delta_y() + v.delta_y();
  temp = Vector2(x,y);
  return temp;
}

Point2 operator+ (Point2 u, Vector2 v)  //  overloaded +
{
  GLfloat x;
  GLfloat y;
  x = u.x + v.delta_x();
  y = u.y + v.delta_y();
  Point2 p(x,y);
  return p;
}

Vector2 operator- (Vector2 u, Vector2 v)  //  overloaded -
{
  GLfloat x;
  GLfloat y;
  Vector2 temp;
  x = u.delta_x() - v.delta_x();
  y = u.delta_y() - v.delta_y();
  temp = Vector2(x,y);
  return temp;
}

GLfloat inner(Vector2 u, Vector2 v)
{
  return u.delta_x() * v.delta_x() + u.delta_y() * v.delta_y();
}

GLfloat operator* (Vector2 u, Vector2 v)
{
  return inner(u,v);
}

Vector2 operator* (GLfloat s, Vector2 u)  // scalar product
{
  Vector2 temp (s * u.delta_x(), s* u.delta_y());
  return temp;
}

Vector2 normalize (Vector2 u)  //  scale to unit length; if zero, stays zero
{

  GLfloat len ;
  len = u.length();

  if (len < EPSILON)
  {
    Vector2 temp(0.0f, 0.0f);
    return temp;
  }
  else
  {
    len = u.length();
    return (1.0f / len) * u;
  }
}

GLfloat cos_angle_between(Vector2 u, Vector2 v)  //return cosine of angle between vectors
{
  return normalize(u) * normalize(v);
}

GLfloat angle_between(Vector2 u, Vector2 v)  //return angle between vectors
{
  return acos ( cos_angle_between(u, v));
}

GLfloat radian_to_degree(GLfloat rad)   // radian to degree  conversion
{
  GLfloat degreesPerRadian = 180 / PIf;
  return rad * degreesPerRadian;
}

Vector2 perp(Vector2 u )
{
  Vector2 temp;
  temp.set(-u.delta_y(), u.delta_x());
  return temp;
}

Vector2 project(Vector2 u, Vector2 v)  // projection of u onto v
{
  // v must be nonzero
  return ((v * u)/(v * v))* v;
}

Vector2 operator- (Point2 q, Point2 p)   // vector from p to q
{
  Vector2 temp;
  temp.set(q.x - p.x, q.y - p.y);
  return temp;
}

Vector2 operator- (Vector2 v)   // unary vector minus
{
  Vector2 temp;
  temp.set(- v.delta_x(), - v.delta_y());
  return temp;
}

Vector2 reflect(Vector2 a, Vector2 m)  // reflection of a in m
{
  Vector2 nm;
  nm = normalize (m);
  return - 1 * (a - (2 * (a * nm)) * nm);
}

GLfloat direction_of(Vector2 v)  // angle in which vector points(radians)
{
  Vector2 nv;
  GLfloat angle;
  if (v.length() < EPSILON)
    return 0.0;
  else
  {
    nv = normalize (v);
    angle = acos(nv.delta_y());
    if (nv.delta_y() < 0.0f)
      return 2 * PIf - angle;
    else
      return angle;
  }
}

 // 2D rays
  Ray2::Ray2( )
  {
    Point2 p;
    Vector2 v;
    base_point = p;  // defaults for point and line
    dir = v;
  }

  Ray2::Ray2(Point2 p, Vector2 v)
  {
    base_point = p;
    dir = v;
  }

  void Ray2::set (Point2 p, Vector2 v)
  {
    base_point = p;
    dir  = v;
  }
//	void draw(void); // draw this ray

  Point2 Ray2::base(void)
  {
    return base_point;
  }// return components

  Vector2 Ray2::direction(void)
  {
    return dir;
  }

  Point2 Ray2:: tip(void)
  {
    return base_point + dir;
  }

   string  Ray2::printable()
   {
       return  "[ray " + base_point.printable() + ", " + dir.printable() + "]";
   }

/*
void ray2:: draw(void) // draw this ray
{
	ray2 r(point, dir);
	ray(r);
}
*/
  Line2::Line2( )  // zero normal; use not advised.
  {
    Point2 p;
    Vector2 v;
    point = p;
    norm = v;
  }

  Line2::Line2(Point2 p, Vector2 v)
  {
    point = p;
    norm = v;
  }

  void Line2::set (Point2 p, Vector2 v)
  {
    point = p;
    norm  = v;
  }
//  draw a line in point-normal form
//	void draw(void); // draw this vector

  Point2 Line2::base(void)
  {
    return point;
  }// return components

  Vector2 Line2::direction(void)
  {
    return perp(norm);
  }

  Vector2 Line2::normal(void)
  {
    return norm;
  }

  string  Line2::printable()
  {
       return  "[line " + point.printable() + ", " + norm.printable() + "]";
   }

