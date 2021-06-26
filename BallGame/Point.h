#ifndef __POINT__
#define __POINT__
#include "openGL.h"
class Point {
protected:
	GLfloat x, y;
public:
	Point();
	Point(GLfloat x, GLfloat y);
	GLfloat getX();
	GLfloat getY();
	void setXY(GLfloat x, GLfloat y);
	void setX(GLfloat x);
	void setY(GLfloat y);
};
#endif