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

void MyQuadTree::IsColliding()
{
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
