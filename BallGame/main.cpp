#include "Headers.h"
GLFWwindow* window;
Ball ball;
string input;
WordsManager words;
bool gameover;

// Diese Funktion wird ebenfalls über Funktionspointer der GLFW-Bibliothek übergeben.
// (Die Signatur ist hier besonders wichtig. Wir sehen, dass hier drei Parameter definiert
//  werden müssen, die gar nicht verwendet werden.)
// Generell überlassen wir der GLFW-Bibliothek die Behandlung der Input-Ereignisse (Mouse moved,
// button click, Key pressed, etc.).
// Durch die Übergabe dieser Funktion können wir Keyboard-Events 
// abfangen. Mouse-Events z. B. erhalten wir nicht, da wir keinen Callback an GLFW übergeben.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (action != GLFW_RELEASE) {       // avoid double updates https://stackoverflow.com/questions/26036315/why-do-i-get-2-callbacks-in-glfw3-opengl

		switch (key)
		{
			// Mit rechte Mousetaste -> gehe zu Deklaration finden Sie andere Konstanten für Tasten.
		case GLFW_KEY_ESCAPE:
			// Das Programm wird beendet, wenn BenutzerInnen die Escapetaste betätigen.
			// Wir könnten hier direkt die C-Funktion "exit" aufrufen, eleganter ist aber, GLFW mitzuteilen
			// dass wir das Fenster schliessen wollen (siehe Schleife unten).
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_BACKSPACE:
			if (!input.empty())
			{
				input.pop_back();
			}
		case ' ':
			break;
		default:
			if (input.length() < 17)
			{
				// Leider auf der amerikanischen tastatur gemapped
				// https://www.reddit.com/r/opengl/comments/etg30e/question_about_glfw3/
				// Keine motivation das jetzt für jeden key einzeln zu bearbeiten, sorry! :)
				input += key;
				printf("%c", key);
			}
			break;
		}

	}

}


// Callback-Mechanismen gibt es in unterschiedlicher Form in allen möglichen Programmiersprachen,
// sehr häufig in interaktiven graphischen Anwendungen. In der Programmiersprache C werden dazu 
// Funktionspointer verwendet. Man übergibt einer aufgerufenen Funktion einer Bibliothek einen
// Zeiger auf eine Funktion, die zurückgerufen werden kann. Die Signatur der Funktion muss dabei
// passen. Dieser Mechanismus existiert auch in C++ und wird hier verwendet, um eine einfache
// Fehlerbehandlung durchzuführen. Diese Funktion gibt Fehler aus, die beim Aufruf von OpenGL-Befehlen
// auftreten.
void error_callback(int error, const char* description)
{
	// Mit fputs gibt man hier den String auf den Standarderror-Kanal aus.
	// In der C-Welt, aus der das hier übernommen ist, sind Strings Felder aus "char"s, die mit 
	// dem Wert null terminiert werden.
	fputs(description, stderr);
}

// OpenGL unterstützt unterschiedliche Shaderprogramme, zwischen denen man
// wechseln kann. Unser Programm wird mit der unsigned-integer-Variable programID
// referenziert.
GLuint programID; 


int main()
{

	// Initialisierung der GLFW-Bibliothek
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// Fehler werden auf stderr ausgegeben, s. o.
	glfwSetErrorCallback(error_callback);

	// Öffnen eines Fensters für OpenGL, die letzten beiden Parameter sind hier unwichtig
	// Diese Funktion darf erst aufgerufen werden, nachdem GLFW initialisiert wurde.
	// (Ggf. glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen -> MacOSX)
	GLFWwindow* window = glfwCreateWindow(700, // Breite
		768,  // Hoehe
		"CG - Tutorial", // Ueberschrift
		NULL,  // windowed mode
		NULL); // shared window

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Wir könnten uns mit glfwCreateWindow auch mehrere Fenster aufmachen...
	// Spätestens dann wäre klar, dass wir den OpenGL-Befehlen mitteilen müssen, in
	// welches Fenster sie "malen" sollen. Wir müssen das aber zwingend auch machen,
	// wenn es nur ein Fenster gibt.

	// Bis auf weiteres sollen OpenGL-Befehle in "window" malen.
	// Ein "Graphic Context" (GC) speichert alle Informationen zur Darstellung, z. B.
	// die Linienfarbe, die Hintergrundfarbe. Dieses Konzept hat den Vorteil, dass
	// die Malbefehle selbst weniger Parameter benötigen.
	// Erst danach darf man dann OpenGL-Befehle aufrufen !
	glfwMakeContextCurrent(window);

	// Initialisiere GLEW
	// (GLEW ermöglicht Zugriff auf OpenGL-API > 1.1)
	glewExperimental = true; // Diese Zeile ist leider notwendig.

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Auf Keyboard-Events reagieren (s. o.)
	glfwSetKeyCallback(window, key_callback);

	// Hiermit wird der text richtig angezeigt
	glEnable(GL_BLEND);     // Transparent Color
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Transparent Color
	glLineWidth(2.0);   // Set drawing line width

	Draw::start();
	Text::init(); 
	
				   
	// Main loop
	int timebase = glfwGetTime();	// timestamp für das erscheinen der neuen worte
	while (!glfwWindowShouldClose(window))
	{
		Draw::draw();

		if (!gameover)
		{
			ball.update();	// Update die bewegung des balls
			words.update(); 
			if (glfwGetTime() - timebase > 3)	// Alle 3 sekunden erscheint ein neues wort aus der liste
			{
				words.generate();
				timebase = glfwGetTime();
			}
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	glfwDestroyWindow(window);
	exit(EXIT_SUCCESS);
	return 0;
}