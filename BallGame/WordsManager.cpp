#include "Headers.h"
extern Ball ball;
extern bool gameover;
extern string input;
WordsManager::WordsManager()
{
	// Lese alle 500 wörter aus der datei
	ifstream in("Words.txt", ios::in);
	for (int i = 0; i < 500; i++)
	{
		string temp;
		in >> temp;
		wordsField[i].set(temp);
	}
	in.close();
}
void WordsManager::generate()
{
	while (1)
	{
		// Das random muss geseedet werden https://stackoverflow.com/a/1108789/6400752
		srand(time(NULL));
		int i = rand() % 499;
		printf("%i", i);
		if (!wordsField[i].isActive())
		{
			wordsField[i].active();
			wordsField[i].setXY(rand() % 590, 675 - rand() % 630);
			break;
		}
	}
		
}

void WordsManager::update()
{
	for (int i = 0; i < 500; i++)
	{
		// Überprüfe nur die aktiven wörter
		if (wordsField[i].isActive())
		{
			// Schaue ob der nutzer ein aktives wort eingetippt hat
			if (input == wordsField[i].get())
			{
				wordsField[i].deactive();
				input.clear();
				break;
			}

			// Kollision zwischen ball und dem wortfeld
			if (ball.getX() + ball.getRadius() >= wordsField[i].getX() &&
				ball.getX() - ball.getRadius() <= wordsField[i].getX() + wordsField[i].getWidth() &&
				ball.getY() + ball.getRadius() >= wordsField[i].getY() &&
				ball.getY() - ball.getRadius() <= wordsField[i].getY() + wordsField[i].getHeight())
			{
				gameover = true;
				break;
			}
		}
	}
}
void WordsManager::draw()
{
	for (int i = 0; i < 500; i++)
	{
		if (wordsField[i].isActive())
		{
			Draw::setColor(1,1,1);
			Draw::rectangle(wordsField[i].getX(), wordsField[i].getY(), 110, 45);
			Text::render(wordsField[i].getX(), wordsField[i].getY(), wordsField[i].get());
		}
	}
}