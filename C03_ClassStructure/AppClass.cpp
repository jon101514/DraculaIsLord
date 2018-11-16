#include "AppClass.h"
// Shader sources
const GLchar* vertexShader = R"glsl(
	#version 330
	in vec3 positionBuffer;
	void main()
	{
		gl_Position = vec4( positionBuffer, 1.0 );
	}
)glsl";
const GLchar* fragmentShader = R"glsl(
	#version 330
	out vec4 fragment;
	void main()
	{
		fragment = vec4( 1.0, 1.0, 0.0, 1.0 );
		return;
	}
)glsl";

//Application Class
AppClass::AppClass() {}
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
	while (running)
	{
		// handle events
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
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
	InitWindow("MyWindow"); //Create Window
	InitOpenGL();			//Initialize Rendering Context
	InitShaders();			//Compile Shaders
	InitVariables();		//Init shape
}
void AppClass::InitWindow(std::string a_sWindowName)
{
	// create the window
	window = new sf::Window(sf::VideoMode(800, 600), a_sWindowName, sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);
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
	// Create and compile the vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	// Create and compile the fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	// Link the vertex and fragment shader into a shader program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	//glBindFragDataLocation(shaderProgramID, 0, "fragment");
	glLinkProgram(shaderProgramID);

	//Check the program
	GLint result = GL_FALSE;
	GLint log = GL_FALSE;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &log);
	if (log > 0) {
		std::vector<char> ProgramErrorMessage(log + 1);
		glGetProgramInfoLog(shaderProgramID, log, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	glUseProgram(shaderProgramID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
void AppClass::InitVariables(void)
{
	GLfloat positions[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
		
	// Create Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);

	// Get the Attribute of position from the shader program
	GLint positionBufferID = glGetAttribLocation(shaderProgramID, "positionBuffer");
	glEnableVertexAttribArray(positionBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
}
void AppClass::ProcessKeyboard(sf::Event a_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		running = false;
}
void AppClass::Display(void)
{
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Color and draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// end the current frame (internally swaps the front and back buffers)
	window->display();
}
void AppClass::Release()
{
	glDeleteShader(shaderProgramID);
	glDeleteBuffers(1, &vbo);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &vao);

	if (window)
	{
		delete window;
		window = nullptr;
	}
}