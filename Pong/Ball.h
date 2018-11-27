/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __BALL_H_
#define __BALL_H_

#include "Simplex\Simplex.h"
#include "MyRigidBody.h"


namespace Simplex
{
//System Class
class Ball
{
	typedef glm::mat4 matrix4;
	typedef glm::vec3 vector3;

	MeshManager* m_pMeshMngr = nullptr; //manages the sphere shape
	RigidBody* m_pRigidBody = nullptr; //manages the collider

	std::vector<vector3> rbPoints; //list of points on the sphere

	vector3 position; //the position of the ball
	matrix4 m_m4ToWorld; //translates the sphere's coordinates to world coordinates

public:
	/*
	Usage: Constructor
	Arguments: 
	Output: class object instance
	*/
	Ball(void);
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	Ball(Ball const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	Ball& operator=(Ball const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~Ball(void);

	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	void Swap(Ball& other);

	/*
	Usage: Moves the ball depending on the forces applied
	Arguments: ---
	Output: ---
	*/
	void Move();

	/*
	Usage: Displays the ball
	Arguments: ---
	Output: ---
	*/
	void Display();

	/*
	Usage: Sets the current position of the ball
	Arguments: vector3 position
	Output: ---
	*/
	void SetPosition(vector3 a_v3Pos);

	/*
	Usage: Gets the current position of the ball
	Arguments: ---
	Output: vector3 position
	*/
	vector3 GetPosition(void);

	void GenerateSphere(int a_nSubdivisions, float a_fRadius);
private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

} //namespace Simplex

#endif //__EXAMPLECLASS_H__

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/