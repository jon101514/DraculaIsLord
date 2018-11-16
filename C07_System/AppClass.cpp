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
		Update();
		Display();
	}
}
void AppClass::Init(void)
{
	// Get the system singleton
	m_pSystem = SystemSingleton::GetInstance();

	InitWindow();	//Create Window

	InitOpenGL();	//Initialize Rendering Context

	//Init light system
	m_pLightMngr = LightManager::GetInstance();
	//Ambient light (Ambient Light is always the first light, or light[0])
	m_pLightMngr->SetPosition(glm::vec3(0, 0, 0), 0);
	m_pLightMngr->SetIntensity(0.75f, 0);
	m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 0);

	//Point Light (light[1])
	m_pLightMngr->SetPosition(glm::vec3(0, 0, 10), 1);
	m_pLightMngr->SetIntensity(5.00f, 1);
	m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 1);

	// Setting the camera position.
	m_pCameraMngr = CameraManager::GetInstance();
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 10.0f));


	m_pMeshMngr = MeshManager::GetInstance(); // Initializing the Mesh manager

	InitShaders();	//Compile Shaders
	
	InitVariables();//Init shape
}
void AppClass::InitWindow()
{
	// create the window
	m_pWindow = new sf::Window(sf::VideoMode(800, 600), m_sWindowName, sf::Style::Default, sf::ContextSettings(32));
	m_pWindow->setVerticalSyncEnabled(true);

	// Get information on the window
	sf::Vector2i pos = m_pWindow->getPosition();
	sf::Vector2u size = m_pWindow->getSize();

	// Indicate window properties
	m_pSystem->SetWindowX(pos.x);
	m_pSystem->SetWindowY(pos.y);

	m_pSystem->SetWindowWidth(size.x);
	m_pSystem->SetWindowHeight(size.y);

	m_pSystem->SetWindowFullscreen(BTO_RESOLUTIONS::RES_WINDOWED);
	m_pSystem->SetWindowBorderless(false);

	// Create icon
	HRSRC rsrcData = FindResource(NULL, L"iconPNG", RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Image image;
	if (!image.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load image from memory.");

	sf::Image icon = image;
	m_pWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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

	// Get information on the window
	sf::Vector2i pos = m_pWindow->getPosition();
	sf::Vector2u size = m_pWindow->getSize();

	// adjust the viewport when the window is resized
	glViewport(0, 0, size.x, size.y);
	m_pMeshMngr->SetRenderTarget(0, 0, 0, size.x, size.y);

	//Init Mesh Manager
	m_pMeshMngr = MeshManager::GetInstance();
}
void AppClass::InitShaders(void)
{
	m_uShaderProgramID = LoadShaders("Shaders//Basic.vs", "Shaders//BasicColor.fs");
	glUseProgram(m_uShaderProgramID);
}
void AppClass::InitVariables(void)
{
	std::vector<vector3> lVertex;

	//vertex 1
	lVertex.push_back(vector3(-0.25f, -0.25f, 0.0f)); //position
	lVertex.push_back(vector3(1.0f, 0.0f, 0.0f)); //color
	//vertex 2
	lVertex.push_back(vector3(0.25f, -0.25f, 0.0f)); //position
	lVertex.push_back(vector3(0.0f, 1.0f, 0.0f)); //color
	//vertex 3
	lVertex.push_back(vector3(0.0f, 0.25f, 0.0f)); //position
	lVertex.push_back(vector3(0.0f, 0.0f, 1.0f)); //color
	
	glGenVertexArrays(1, &m_uVAO);//Generate vertex array object
	glGenBuffers(1, &m_uVBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_uVAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);//Bind the VBO

	//Generate space for the VBO (vertex count times size of vec3)
	glBufferData(GL_ARRAY_BUFFER, lVertex.size() * sizeof(vector3), &lVertex[0], GL_STATIC_DRAW);

	//count the attributes
	int attributeCount = 2;
	
	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	//Done with m_uVAO change the active VAO to safe location
	glBindVertexArray(0);
}
void AppClass::ProcessKeyboard(sf::Event a_event)
{
	if (a_event.key.code == sf::Keyboard::Key::Escape)//Event says I pressed the Escape key
		m_bRunning = false;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //I am currently pressing the Num1 (not the same as above)
		m_v3Color = vector3(1.0f, 0.0f, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		m_v3Color = vector3(0.0f, 1.0f, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		m_v3Color = vector3(0.0f, 0.0f, 1.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		m_v3Color = vector3(-1.0f, -1.0f, -1.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_m4Model = glm::translate(m_m4Model, vector3(-0.1f, 0.0f, 0.0f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_m4Model = glm::translate(m_m4Model, vector3( 0.1f, 0.0f, 0.0f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_m4Model = glm::translate(m_m4Model, vector3(0.0f, -0.1f, 0.0f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_m4Model = glm::translate(m_m4Model, vector3(0.0f, 0.1f, 0.0f));
}
void AppClass::ProcessMouse(void)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
	}

	for (int i = 0; i < 3; i++)
	{
	}
}
void AppClass::Update(void)
{
	//Update the system
	m_pSystem->Update();
}
void AppClass::Display(void)
{
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Add skybox to the list
	m_pMeshMngr->AddSkyboxToRenderList();

	//Bind the VAO for the triangle
	glBindVertexArray(m_uVAO);
	glUseProgram(m_uShaderProgramID);

	//View and projection matrix
	matrix4 m4View;//view matrix
	matrix4 m4Projection;//projection matrix
	
	//read uniforms and send values
	GLuint MVP = glGetUniformLocation(m_uShaderProgramID, "MVP");//Model View Projection
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4Projection * m4View * m_m4Model));
	
	GLuint SolidColor = glGetUniformLocation(m_uShaderProgramID, "SolidColor"); //custom color of the shape
	glUniform3f(SolidColor, m_v3Color.r, m_v3Color.g, m_v3Color.b);
		
	//draw content
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	//Bind the VAO for the triangle
	glBindVertexArray(0);
	
	//Display render list
	m_pMeshMngr->Render();

	//Clear the render list for the next try
	m_pMeshMngr->ClearRenderList();
		
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