#ifndef __BALL__
#define __BALL__
#include "openGL.h"
#include "Point.h"
class Ball :public Point {
	int radius;
	GLfloat winkel, speed;
public:
	Ball();
	int getRadius();
	void setRadius(int radius);
	void update();
	GLfloat getAngle();
	void setAngle(GLfloat);
	GLfloat getSpeed();
	void setSpeed(GLfloat);
	void draw();
	void reverseX();
	void reverseY();
	
};
#endif
