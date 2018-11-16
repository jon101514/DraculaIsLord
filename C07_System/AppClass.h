/*----------------------------------------------
Programmer: Alberto Bobadilla(labigm@gmail.com)
Date : 2018 / 01
----------------------------------------------*/
#ifndef __APPCLASS_H_
#define __APPCLASS_H_

#include "Framework.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class AppClass 
{
	std::string m_sWindowName = ""; //window name
	sf::Window* m_pWindow = nullptr; //SFML window
	GLuint m_uShaderProgramID = 0; //Shader program
	GLuint m_uVAO = 0; //Vertex Array Object
	GLuint m_uVBO = 0; //Vertex Buffer Object
	
	matrix4 m_m4Model = matrix4(1.0f); //Identity matrix
	vector3 m_v3Color = vector3(-1.0f); //Color of shape

	bool m_bRunning = true; //Running Flag

	SystemSingleton* m_pSystem = nullptr;// Singleton of the system

	GLSystem* m_pGLSystem = nullptr;// Singleton of the OpenGL rendering context

	MaterialManager* m_pMatMngr = nullptr;// singleton for the material manager
	LightManager* m_pLightMngr = nullptr;// Singleton for the Light Manager
	MeshManager* m_pMeshMngr = nullptr;//Mesh Manager
	CameraManager* m_pCameraMngr = nullptr; // Singleton for the camera that represents our scene
	
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	AppClass(std::string a_windowName);
	/*
	USAGE: Destroys instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void);
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Run(void);

private:
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	AppClass(AppClass const& input);
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	AppClass& operator=(AppClass const& input);

	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Initialize the window
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitWindow(void);
	/*
	USAGE: Initialize the OpenGL Context
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitOpenGL(void);
	/*
	USAGE: Initialize the OpenGL Shaders
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitShaders(void);
	/*
	USAGE: Initializes user specific variables, this is executed right after InitWindow,
	the purpose of this member function is to initialize member variables specific for this project.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitVariables(void);
	/*
	USAGE: Releases the application
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyboard(sf::Event a_event);
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouse(void);
};

#endif //__APPCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/