#include "Ball.h"

using namespace Simplex;

void Ball::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();

	//set the position of the sphere to the center of the world
	position = vector3(0);
	m_m4ToWorld = glm::translate(position);
	
	//create the rigidbody for collision
	m_pRigidBody = new RigidBody(rbPoints);
}
void Ball::Swap(Ball& other)
{
	//std::swap(m_nData, other.m_nData);

}
void Simplex::Ball::Move()
{
}
void Simplex::Ball::Display()
{
	//generate the sphere and show it
	m_pMeshMngr->AddSphereToRenderList(m_m4ToWorld, C_VIOLET);
}
void Simplex::Ball::SetPosition(vector3 a_v3Pos)
{
	position = a_v3Pos;
}
vector3 Simplex::Ball::GetPosition(void)
{
	return position;
}
void Ball::Release(void)
{
	SafeDelete(m_pRigidBody);
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


