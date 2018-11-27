#include "Ball.h"

using namespace Simplex;

void Ball::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();

	//set the position of the sphere to the center of the world
	m_m4ToWorld = glm::translate(vector3(0));

	GenerateSphere(12, 1.0f);
	
	//create the rigidbody for collision
	m_pRigidBody = new MyRigidBody(rbPoints);

	//set the initial direction 
	direction = vector3(1, 0, 0);

	//set the speed
	speed = 1.0f;
}
void Ball::Swap(Ball& other)
{
	//std::swap(m_nData, other.m_nData);

}
void Simplex::Ball::Move(float deltaTime)
{
	//change the position
	//position = position + (direction * speed * deltaTime);

	//translate the ball from its old position to the new position
	m_m4ToWorld = glm::translate(m_m4ToWorld, (direction * speed * deltaTime));

	//update the rigid body
	m_pRigidBody->SetModelMatrix(m_m4ToWorld);
}
void Simplex::Ball::Display()
{
	//generate the sphere and show it
	m_pMeshMngr->AddSphereToRenderList(m_m4ToWorld, C_VIOLET);
}
void Simplex::Ball::GenerateSphere(int a_nSubdivisions, float a_fRadius)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		return;
	}

	if (a_nSubdivisions > 36)
		a_nSubdivisions = 36;

	rbPoints.clear();
	// Replace this with your code
	//top and bottom of sphere
	vector3 top(0, a_fRadius, 0);
	vector3 bottom(0, -a_fRadius, 0);

	//holds the vertices of full sphere
	//the -2 is because I am counting top and bottom as a subdivision, so there are the same number of face divisions vertical as horizontal
	vector3** vertices = new vector3*[a_nSubdivisions - 2];
	for (int i = 0; i < a_nSubdivisions - 2; i++)
	{
		vertices[i] = new vector3[a_nSubdivisions];
	}

	//I'm rotating this point up and down to find where to start each xz-flat circle
	vector3 midstartpoint(a_fRadius, 0, 0);

	//angle each point is from the others
	float angle = (float)PI * 2 / (a_nSubdivisions);
	//make circle
	for (int i = 0; i < a_nSubdivisions - 2; i++)
	{

		//makes it so that the sphere is centered and that we are finding one of the sides along the y-axis
		float centeringNumber = i + 1 - (a_nSubdivisions - 1) / 2.0f;

		//angle / 2 makes it so that we only get points for half the circle
		//we make a rotation matrix that finds a point given the far right side of the sphere, then we rotate that far right point to find the point we want
		matrix3 transformation = matrix3(cosf(angle / 2 * centeringNumber), -sinf(angle / 2 * centeringNumber), 0, sinf(angle / 2 * centeringNumber), cosf(angle / 2 * centeringNumber), 0, 0, 0, 1);
		vertices[i][0] = midstartpoint * transformation;
	}

	//take each point along the right side of the sphere and create a circle on the xz plane out of it
	for (int i = 0; i < a_nSubdivisions - 2; i++)
	{
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			//make a rotation matrix and rotate the point to find the new points
			matrix3 transformation = matrix3(cosf(angle * j), 0, sinf(angle * j), 0, 1, 0, -sinf(angle * j), 0, cosf(angle * j));
			vertices[i][j] = vertices[i][0] * transformation;
		}
	}

	//add the quads
	for (int i = 0; i < a_nSubdivisions - 3; i++)
	{
		for (int j = 0; j < a_nSubdivisions - 1; j++)
		{
			//add a quad along each xz circle
			rbPoints.push_back(vertices[i][j]);
		}
	}

	//clean memory
	for (int i = 0; i < a_nSubdivisions - 2; i++)
	{
		if (vertices[i] != nullptr) {
			delete[] vertices[i];
			vertices[i] = nullptr;
		}
	}

	if (vertices != nullptr) {
		delete[] vertices;
		vertices = nullptr;
	}
}
void Simplex::Ball::ChangeDirection(vector3 newDirection)
{
	direction = glm::normalize(newDirection);
}
void Simplex::Ball::ChangeSpeed()
{
	speed = speed + 0.5f;
}
void Ball::Release(void)
{
	SafeDelete(m_pRigidBody);
}
RigidBody* Simplex::Ball::GetRigidBody(void)
{
	return m_pRigidBody;
}
//The big 3
Ball::Ball(){Init();}
Ball::Ball(Ball const& other)
{
	
}
Ball& Ball::operator=(Ball const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		Ball temp(other);
		Swap(temp);
	}
	return *this;
}
Ball::~Ball(){Release();};




