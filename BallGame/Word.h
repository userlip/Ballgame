#ifndef __WORD__
#define __WORD__
#include "Point.h"
#include <string>
class Word:public Point
{
	string word;
	bool show;	// Indicates if the word should be shown in display
	GLfloat height, width;
public:
	Word();
	void set(string);
	string get();
	void active();
	void deactive();
	bool isActive();
	void setWidth(GLfloat width);
	void setHeight(GLfloat height);
	GLfloat getHeight();
	GLfloat getWidth();
};
#endif
