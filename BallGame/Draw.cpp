#include "Headers.h"
extern bool gameover;
extern WordsManager words;
extern Ball ball;
extern string input;

vector<Draw::vertice> Draw::vertices;
float Draw::r, Draw::g, Draw::b, Draw::a; // Farben
unsigned int Draw::shaderProgram; // Das ist das kombinierte shader https://learnopengl.com/Getting-started/Hello-Triangle
unsigned int Draw::VBO;
unsigned int Draw::VAO;


// Shader Hilfe: https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
// https://learnopengl.com/Getting-started/Hello-Triangle

const GLchar* Draw::vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position =  projection * model * vec4(aPos,0.0, 1.0);\n"
"}";

const GLchar* Draw::fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}";


void Draw::draw()
{
	clear();
	if (gameover)
	{

		// GAME OVER in der mitte des windows
		setColor(1,1,1);
		Text::render(165,320, "GAME OVER" ,2);
	}

	else
	{
		ball.draw();
		words.draw();

		// Der weisse balken unten für die eingabe
		setColor(1,1,1);
		Draw::filledRectangle(0, 0, 700, 45);
		 

		// Der Text in schwarz welcher auf dem weissen balken angezeigt wird
		setColor(0,0,0);
		Text::render(295, 0, input);
	}
	
}
