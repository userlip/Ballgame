#include "Headers.h"
Ball::Ball()
{
	// Der Ball soll random im Spiel starten und mit einem random winkel los "fliegen"
	// Das random muss geseedet werden https://stackoverflow.com/a/1108789/6400752
	srand(time(NULL));

	x = rand() %700;
	y = 745-rand() %700;
	radius = 20;
	winkel = rand() %360;
	speed = 0.1;
}

int Ball::getRadius()
{
	return radius;
}
void Ball::setRadius(int radius)
{
	this->radius = radius;
}
GLfloat Ball::getAngle()
{
	return winkel;
}
void Ball::setAngle(GLfloat winkel)
{
	this->winkel = winkel;
}

void Ball::reverseX()
{
	winkel = PI - winkel;
	this->setSpeed(this->getSpeed() * 1.05); // Ball wird schneller wenn er kante berührt
}
void Ball::reverseY()
{
	winkel = 2 * PI - winkel;
	this->setSpeed(this->getSpeed() * 1.05); // Ball wird schneller wenn er kante berührt
}
void Ball::update()
{
	// https://stackoverflow.com/a/5193031/6400752
	x += speed * cos(winkel);
	y += speed * sin(winkel);

	if (y > 745 - radius)
	{
		reverseY();
		y = 745 - radius;
	}
	else if (x < radius)
	{
		reverseX();
		x = radius;
	}
	else if (x > 700 - radius)
	{
		reverseX();
		x = 700 - radius;
	}
	if (y < 45 + radius)
	{
		reverseY();
		y = 45 + radius;
	}
}


void Ball::draw()
{

	// Weisse farbe für den ball
	Draw::setColor(1,1,1);
	Draw::filledCircle(x, y, radius);
}

GLfloat Ball::getSpeed()
{
	return speed;
}
void Ball::setSpeed(GLfloat speed)
{
	this->speed = speed;
}