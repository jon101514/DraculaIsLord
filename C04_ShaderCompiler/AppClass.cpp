#include "AppClass.h"
//Application Class
AppClass::AppClass(std::string a_windowName) : m_sWindowName(a_windowName) {}
AppClass::AppClass(AppClass const& input) {}
AppClass& AppClass::operator=(AppClass const& input) { return *this; }
AppClass::~AppClass(void){ Release(); }
void AppClass::Run(void)
{
	//Initialize the system with the fields recollected by the constructor
	Init();
	
	//Set the background color
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	// run the main loop
	while (m_bRunning)
	{
		// handle events
		sf::Event event;
		while (m_pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				m_bRunning = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				ProcessKeyboard(event);
			}
		}

		Display();
	}
}
void AppClass::Init(void)
{
	InitWindow(); //Create Window
	InitOpenGL();			//Initialize Rendering Context
	InitShaders();			//Compile Shaders
	InitVariables();		//Init shape
}
void AppClass::InitWindow()
{
	// create the window
	m_pWindow = new sf::Window(sf::VideoMode(800, 600), m_sWindowName, sf::Style::Default, sf::ContextSettings(32));
	m_pWindow->setVerticalSyncEnabled(true);
}
void AppClass::InitOpenGL(void)
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit(); //run glew setup

	glEnable(GL_BLEND);	//Enable pixel blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //type of the blend function

	glEnable(GL_DEPTH_TEST);// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);	//Don't show faces from behind
}
void AppClass::InitShaders(void)
{
	m_uShaderProgramID = LoadShaders("Shaders//Minimal.vs", "Shaders//Minimal.fs");
	glUseProgram(m_uShaderProgramID);
}
void AppClass::InitVariables(void)
{
	GLfloat positions[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Create Vertex Array Object
	glGenVertexArrays(1, &m_uVAO);
	glBindVertexArray(m_uVAO);
		
	// Create Vertex Buffer Object
	glGenBuffers(1, &m_uVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);

	// Get the Attribute of position from the shader program
	GLint positionBufferID = glGetAttribLocation(m_uShaderProgramID, "positionBuffer");
	glEnableVertexAttribArray(positionBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}
void AppClass::ProcessKeyboard(sf::Event a_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_bRunning = false;
}
void AppClass::Display(void)
{
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Color and draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void AppClass::Release()
{
	glDeleteShader(m_uShaderProgramID);
	glDeleteBuffers(1, &m_uVBO);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &m_uVAO);

	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}
}