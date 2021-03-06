/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __BALL_H_
#define __BALL_H_

#include <random>
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
	MyRigidBody* m_pRigidBody = nullptr; //manages the collider

	std::vector<vector3> rbPoints; //list of points on the sphere

	vector3 position;
	vector3 direction; //the direction of the ball
	float speed; //the speed of the ball
	matrix4 m_m4ToWorld; //translates the sphere's coordinates to world coordinates

	bool hasScored = false; // Whether or not this ball has been accounted for in terms of score.

public:
	MyRigidBody* GetRigidBody(void);
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
	Usage: Getter for hasScored boolean.
	Arguments: ---
	Output: whether or not this ball has been used to calculate score.
	*/
	bool GetHasScored(void);
	/*
	Usage: Setter for hasScored boolean.
	Arguments: 
	bool newVal -> The new boolean value of hasScored.
	Output: ---
	*/
	void SetHasScored(bool newVal);
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
	Arguments: Pass time in from the update
	Output: ---
	*/
	void Move(float deltaTime);

	void Move(vector3 moveVector);
	/*
	Usage: Displays the ball
	Arguments: ---
	Output: ---
	*/
	void Display();

	/*
	Usage: Generates the points of a sphere for the rigidbody
	Arguments: number of subdivisions in the sphere, size
	Output: ---
	*/
	void GenerateSphere(int a_nSubdivisions, float a_fRadius);

	/*
	Usage: Changes the ball's direction
	Arguments: a new direction to set the ball to
	Output: ---
	*/
	void ChangeDirection(vector3 newDirection);

	/*
	Usage: Gets the ball's positions
	Arguments: ---
	Output: ---
	*/
	vector3 GetPosition();

	/*
	Usage: Gets the ball's direction
	Arguments: ---
	Output: ---
	*/
	vector3 GetDirection();

	/*
	Usage: Changes the ball's speed
	Arguments: ---
	Output: ---
	*/
	void ChangeSpeed();
	void Release(void);

private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	//void Release(void);
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