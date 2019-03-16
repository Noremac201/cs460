#ifndef LINEAR_ALGEBRA_H_INCLUDED
#define LINEAR_ALGEBRA_H_INCLUDED

#include <cmath>
#include <iostream>  //  may not be needed.
#include <string>   //  may not be needed.
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

// using namespace std;

// linear_algebra.h
// 2 and 3 dimensional points and vectors
// definitions of things useful with vectors.
//  loosely based on CH 4 of Hill

// This is intended for use with OpenGL.  That is why GLfloat is used.
// However, the algebra in here has no connection to OpenGL.
// In practice, GLfloat is float on all versions in use.

//  Points in 2D

class Point2
{
public:
  float x,y;
  Point2();

  Point2(GLfloat xx, GLfloat yy);

  void set(GLfloat xx, GLfloat yy);

// make a printable representation.
  std::string printable();

  void draw(void);
};

static Point2 ORIGIN2 (0.0f, 0.0f);			//  origin of 2D plane

// vectors in  2D

class Vector2
{
public:
  Vector2();

  Vector2(GLfloat x, GLfloat y);

  // creates a unit vector in direction angle
  // anticlockwise from right
  Vector2(GLfloat angle);

  void set (GLfloat x, GLfloat y);


  std::string printable(void);

//	void draw(void); // draw this vector

  GLfloat length(void);

  GLfloat delta_x(void);	// return components
  GLfloat delta_y(void);

private:
  GLfloat dx;
  GLfloat dy;
};

Vector2 perp(Vector2 u );

class Ray2
{
public:
  Ray2( );

  Ray2(Point2 p, Vector2 v);

  void set (Point2 p, Vector2 v);

//	void draw(void); // draw this ray

  // return components
  Point2 base(void);

  Vector2 direction(void);

  Point2 tip(void);

   std::string printable();

private:
  Point2 base_point;
  Vector2 dir ;
};

class Line2
{
public:
  Line2( );  // zero normal; use not advised.

  Line2(Point2 p, Vector2 v);

  void set (Point2 p, Vector2 v);

//  draw a line in point-normal form
//	void draw(void); // draw this vector

  Point2 base(void);

  Vector2 direction(void);

  Vector2 normal(void);

   std::string printable();

private:
  Point2 point;
  Vector2 norm ;
};

static Vector2 i2 = Vector2(1.0f, 0.0f);
static Vector2 j2(0.0f, 1.0f);

GLfloat inner(Vector2 u, Vector2 v);

Vector2 operator+ (Vector2 u, Vector2 v); //  overloaded +

Vector2 operator- (Vector2 u, Vector2 v);  //  overloaded -

Point2 operator+ (Point2 u, Vector2 v); //  overloaded +

GLfloat operator* (Vector2 u, Vector2 v);   // inner product

Vector2 operator* (GLfloat s, Vector2 u);  // scalar product

Vector2 normalize (Vector2 u);      //  scale to unit length; if zero, stays zero

GLfloat cos_angle_between(Vector2 u, Vector2 v);  //return cosine of angle between vectors

GLfloat angle_between(Vector2 u, Vector2 v);  //return angle between vectors

GLfloat radian_to_degree(GLfloat rad);   // radian to degree  conversion

Vector2 project(Vector2 u, Vector2 v);  // projection of u onto v

Vector2 operator- (Point2 q, Point2 p);   // vector from p to q
Vector2 operator- (Vector2 v);   // unary vector minus

Vector2 reflect(Vector2 a, Vector2 m);  // reflection of a in m

GLfloat direction_of(Vector2 v);  // angle in which vector points(radians)


#endif // LINEAR_ALGEBRA_H_INCLUDED
