/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/04
----------------------------------------------*/
#ifndef __FRAMEWORK_H_
#define __FRAMEWORK_H_

#pragma warning( disable : 4251 )

#include "Definitions.h" //ReEng basic Definitions
#include "SystemSingleton.h" //System related methods

#include "Window.h" //WinAPI encapsulated methods
#include "FileReader.h" //Reads an object and returns lines as strings
#include "Folder.h" //Sets the working directory
#include "GLSystem.h" //OpenGL 2.0 and 3.0 initialization

#include "ShaderManager.h" //Shader Manager, loads and manages different shader files
#include "ShaderCompiler.h" //Compiles the shader objects

#include "LightManager.h" //Manages the light sources of the world

#include "MaterialManager.h" //Manages the materials
#include "TextureManager.h" //Manages the Textures, loads, display and release

#include "Text.h" //Singleton for drawing Text on the screen
#include "Mesh.h"//Mesh class
#include "MeshManager.h"//Mesh Singleton

#include "CameraManager.h" //Creates and manages the camera object for the world

/*
ReleaseAllSingletons
USAGE: Releases all ReEngine Singletons
ARGUMENTS: ---
OUTPUT: ---
*/
static void ReleaseAllSingletons(void)
{
	LightManager::ReleaseInstance();
	MaterialManager::ReleaseInstance();
	TextureManager::ReleaseInstance();
	CameraManager::ReleaseInstance();
	Folder::ReleaseInstance();
	GLSystem::ReleaseInstance();
	ShaderManager::ReleaseInstance();
	SystemSingleton::ReleaseInstance();
	Text::ReleaseInstance();
	MeshManager::ReleaseInstance();
}
#endif //__BASICXFRAMEWORK_H_