#ifndef __DRAW__
#define __DRAW__
#include "Headers.h"
#define PI (acos(-1.0))
class Draw {
public:
	struct vertice
	{
		GLfloat x, y;
	};
	static vector<vertice> vertices;
	static float r, g, b, a;
	static const GLchar* vertexShaderSource;
	static const GLchar* fragmentShaderSource;
	static unsigned int shaderProgram, VBO, VAO;
	
	static void display(void)		// Mal alles auf den Bildschirm
	{
		draw();
	}
	static void clear()	// Lösche das gemalte
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	static unsigned int createProgram()
	{

		// https://learnopengl.com/Getting-started/Hello-Triangle
		unsigned int  vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// fragment shader
		unsigned int  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// link shaders
		unsigned int  shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}
	static void start()
	{
		r = g = b = 0.0f;
		a = 1.0f;
		shaderProgram = createProgram();
		
		//https://learnopengl.com/Getting-Started/Coordinate-Systems
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(700), 0.0f, static_cast<float>(745));
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0,0,0));
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}
	
	static void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	static void filledShape()
	{

		//https://learnopengl.com/Getting-started/Hello-Triangle

		// ..:: Initialization code :: ..
		// 1. bind Vertex Array Object
		glBindVertexArray(VAO); // Ansonten sind die text kästen weiss!!

		// 2. copy our vertices array in a vertex buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		
		// 3. then set the vertex attributes pointers
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), r, g, b, a);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

		vertices.clear();
	}
	static void shape()
	{

		// link von oben
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), r, g, b, a);
		glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

		vertices.clear();
	}

	static void filledCircle(float x, float y, float r, GLint slices = 100)
	{
		// Ausgemalter ball
		float t, dt = 2 * PI / slices;
		for (t = 0; t <= 2 * PI + dt; t += dt)
		{
			float x1, y1;
			x1 = (x + r * cos(t));
			y1 = (y + r * sin(t)),
				vertices.push_back({ x1, y1 });
		}
		filledShape();
	}

	// Das rechteck für den text und die collision
	static void rectangle(float left, float bottom, float width, float height)
	{
		float x1, x2, y1, y2;
		x1 = left,
		y1 = bottom,
		x2 = ((left + width)),
		y2 = ((bottom + height));

		vertices.push_back({ x1, y1 });
		vertices.push_back({ x2, y1 });
		vertices.push_back({ x2, y2 });
		vertices.push_back({ x1, y2 });
		vertices.push_back({ x1, y1 });
		shape();
	}

	// Für die weisse box am unteren bildschirmrand für die texteingabe
	static void filledRectangle(float left, float bottom, float width, float height)
	{
		float x1, x2, y1, y2;
		x1 = left,
		y1 = bottom,
		x2 = ((left + width)),
		y2 = ((bottom + height));

		vertices.push_back({ x1, y1 });
		vertices.push_back({ x2, y1 });
		vertices.push_back({ x2, y2 });
		vertices.push_back({ x1, y2 });
		filledShape();
	}
	static void draw();
};
#endif
