#include "MyQuadTree.h"
using namespace Simplex;


void MyQuadTree::Init()
{

}

void MyQuadTree::Release()
{
	for (uint i = 0; i < 4; i++)
	{
		SafeDelete(m_pChildren[i]);
	}

	SafeDelete(mainQuad);
}

void Simplex::MyQuadTree::Swap(MyQuadTree & other)
{
	std::swap(m_uID, other.m_uID);
	std::swap(m_uLevel, other.m_uLevel);

	for (uint i = 0; i < 4; i++)
	{
		if (other.m_pChildren[i] != NULL)
			std::swap(m_pChildren[i], other.m_pChildren[i]);
	}

	std::swap(m_fSize, other.m_fSize);

	std::swap(m_ContainedObjects, other.m_ContainedObjects);

	std::swap(mainQuad, other.mainQuad);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_pRoot, other.m_pRoot);

	std::swap(m_lChild, other.m_lChild);
}

MyQuadTree::MyQuadTree(std::vector<MyRigidBody*> rbList)
{
	Init();

	//set it to the very first octant, the big octant
	m_pRoot = this;

	//get the entity list and the count
	m_ContainedObjects = rbList;

	std::vector<vector3> m_v3List;

	for (uint i = 0; i < m_ContainedObjects.size(); i++)
	{
		m_v3List.push_back(m_ContainedObjects[i]->GetMaxGlobal());
		m_v3List.push_back(m_ContainedObjects[i]->GetMaxGlobal());
	}

	mainQuad = new MyRigidBody(m_v3List);

	for (int i = 0; i < 4; i++)
	{
		m_pChildren[i] = nullptr;
	}
}

Simplex::MyQuadTree::MyQuadTree(vector3 center, float size)
{
	Init();
	std::vector<vector3> v3MaxMin_List;

	//calculate the max and min and push onto list
	v3MaxMin_List.push_back(center - vector3(size));
	v3MaxMin_List.push_back(center + vector3(size));

	//create the root shell
	mainQuad = new MyRigidBody(v3MaxMin_List);

	m_v3Max = mainQuad->GetMaxGlobal();
	m_v3Min = mainQuad->GetMinGlobal();
}

MyQuadTree::~MyQuadTree()
{
	Release();
}

Simplex::MyQuadTree::MyQuadTree(MyQuadTree const & other)
{
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;

	for (uint i = 0; i < 4; i++)
	{
		if (other.m_pChildren[i] != NULL)
			m_pChildren[i] = other.m_pChildren[i];
	}

	m_fSize = other.m_fSize;

	m_ContainedObjects = other.m_ContainedObjects;

	mainQuad = other.mainQuad;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_pRoot = other.m_pRoot;

	m_lChild = other.m_lChild;
}

MyQuadTree & Simplex::MyQuadTree::operator=(MyQuadTree const & other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyQuadTree temp(other);
		Swap(temp);
	}
	return *this;
}

bool MyQuadTree::IsColliding(MyRigidBody* collider)
{
	//initial collision check
	bool bColliding = true;

	//if any of these are colliding, check sphere collision
	if (bColliding) {
		if (m_v3Max.x < collider->GetMinGlobal().x) {
			bColliding = false;
		}
		if (m_v3Min.x > collider->GetMaxGlobal().x) {
			bColliding = false;
		}
		if (m_v3Max.y < collider->GetMinGlobal().y) {
			bColliding = false;
		}
		if (m_v3Min.y > collider->GetMaxGlobal().y) {
			bColliding = false;
		}
	}

	//now check for sphere collision
	if (bColliding) {
		for (uint i = 0; i < m_ContainedObjects.size(); i++)
		{
			return this->m_ContainedObjects[i]->IsCollidingSphere(collider);
		}
	}
	else {
		return false;
	}
}

void MyQuadTree::Display()
{
	mainQuad->AddToRenderList();

	if (m_pChildren[0] != nullptr) {
		/*for (uint i = 0; i < 4; i++)
		{
			m_pChildren[i]->Display();
		}*/
		m_pChildren[0]->Display();
	}
}

void Simplex::MyQuadTree::AddEntity(MyRigidBody * entity)
{
	m_ContainedObjects.push_back(entity);
}

void MyQuadTree::Subdivide(int maxLevel, int ideal_Count)
{
	//stops the recursive process
	if (m_uLevel >= maxLevel || m_ContainedObjects.size() <= ideal_Count) {
		m_pRoot->m_lChild.push_back(this);
		return;
	}
		
	//allocate the smaller octants of this big octant
	vector3 v3Center = mainQuad->GetCenterLocal();
	vector3 v3HalfWidth = mainQuad->GetHalfWidth();
	float fSize = (v3HalfWidth.x) / 2.0f;
	float fCenters = fSize;

	m_pChildren[0] = new MyQuadTree(v3Center + vector3(fCenters, fCenters, 0), fSize);
	m_pChildren[1] = new MyQuadTree(v3Center + vector3(-fCenters, fCenters, 0), fSize);
	m_pChildren[2] = new MyQuadTree(v3Center + vector3(-fCenters, -fCenters, 0), fSize);
	m_pChildren[3] = new MyQuadTree(v3Center + vector3(fCenters, -fCenters, 0), fSize);


	for (uint i = 0; i < 4; i++)
	{
		//check every entity under the child
		for (uint j = 0; j < m_ContainedObjects.size(); j++)
		{
			if (m_pChildren[i]->IsColliding(m_ContainedObjects[j])) {
				m_pChildren[i]->m_ContainedObjects.push_back(m_ContainedObjects[j]);
			}
		}
		
		m_pChildren[i]->m_uID = i * glm::pow(10, m_uID) + m_uID;

		//increment level
		m_pChildren[i]->m_uLevel = m_uLevel + 1;
		//set all children's root to the big octant
		m_pChildren[i]->m_pRoot = m_pRoot;
		//recursive
		m_pChildren[i]->Subdivide(maxLevel, ideal_Count);
	}
}

bool MyQuadTree::IsLeaf()
{
	return m_pChildren[0] == nullptr && !m_ContainedObjects.empty();
}

void MyQuadTree::ConstructList(int maxLevel, int ideal_Count)
{
	Subdivide(maxLevel, ideal_Count);
	AssignID();
}

void MyQuadTree::KillBranches()
{
	m_lChild.clear();

	for (uint i = 0; i < 4; i++)
	{
		SafeDelete(m_pChildren[i]);
	}
}

void Simplex::MyQuadTree::AssignID()
{
	AnnihilateID();

	uint leafCount = m_lChild.size();
	
	
	for (uint i = 0; i < leafCount; i++)
	{
		uint entityCount = m_lChild[i]->m_ContainedObjects.size();

		for (uint j = 0; j < entityCount; j++)
		{
			m_lChild[i]->m_ContainedObjects[j]->AddDimension(m_lChild[i]->m_uID);
		}
	}
}

void Simplex::MyQuadTree::AnnihilateID()
{
	uint entityCount = m_ContainedObjects.size();

	for (uint i = 0; i < entityCount; i++)
	{
		m_ContainedObjects[i]->ClearDimensionList();
	}
}
