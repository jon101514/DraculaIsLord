/*----------------------------------------------
Programmer: Alberto Bobadilla(labigm@gmail.com)
Date : 2018 / 01
----------------------------------------------*/
#ifndef __APPCLASS_H_
#define __APPCLASS_H_

#include <stdio.h>
#include <stdlib.h>

#include <GL\glew.h>
#include <GL\wglew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class AppClass 
{
	sf::Window* window = nullptr; //SFML window
	GLuint shaderProgramID = 0;
	GLuint vao = 0;
	GLuint vbo = 0;
	bool running = true;
	
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	AppClass();
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
	ARGUMENTS:
	String a_sWindowName = "GLFW" -> Window name
	OUTPUT: ---
	*/
	void InitWindow(std::string a_sWindowName = "Window");
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
};

#endif //__SFMLAPPCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/