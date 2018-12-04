#include "MyQuadTree.h"
using namespace Simplex;


void MyQuadTree::Init()
{
}

void MyQuadTree::Delete()
{
}

MyQuadTree::MyQuadTree(std::vector<MyRigidBody*> rbList)
{
	Init();

	//set it to the very first octant, the big octant
	m_pRoot = this;

	//get the entity list and the count
	m_containedObjects = rbList;
}

Simplex::MyQuadTree::MyQuadTree(vector3 center, float size)
{
}


MyQuadTree::~MyQuadTree()
{
}

bool MyQuadTree::IsColliding(MyRigidBody collider)
{
	if (m_v3Max.x < collider.GetMinGlobal().x) {

		return false;
	}
	if (m_v3Min.x > collider.GetMaxGlobal().x) {

		return false;
	}
	if (m_v3Max.y < collider.GetMinGlobal().y) {

		return false;
	}
	if (m_v3Min.y > collider.GetMaxGlobal().y) {

		return false;
	}

	return true;
}

void MyQuadTree::Display()
{
}

void MyQuadTree::Subdivide()
{
}

bool MyQuadTree::IsLeaf()
{
	return m_pChildren[0] == nullptr && !m_containedObjects.empty();
}

void MyQuadTree::ConstructList(int maxLevel, int ideal_Count)
{
}

void MyQuadTree::KillBranches()
{
}

void Simplex::MyQuadTree::AssignID()
{
}

void Simplex::MyQuadTree::AnnihilateID()
{
}
