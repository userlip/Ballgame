#include "Word.h"
Word::Word()
{
	width = 140; // Ausreichend f�r die alle 5 buchstaben langen w�rter
	height = 45;
}
void Word::set(string word)
{
	this->word = word;
}
string Word::get()
{
	return word;
}
void Word::active()
{
	show = true;
}
void Word::deactive()
{
	show = false;
}
bool Word::isActive()
{
	return show;
}

void Word::setWidth(GLfloat width)
{
	this->width = width;
}
void Word::setHeight(GLfloat height)
{
	this->height = height;
}
GLfloat Word::getHeight()
{
	return this->height;
}
GLfloat Word::getWidth()
{
	return this->width;
}