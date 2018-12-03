#pragma once
#include <vector>
#include "MyRigidBody.h"

namespace Simplex
{
class MyQuadTree
{
	uint m_uID = 0;

	MyQuadTree* m_pChildren[8];

	float m_fSize = 0.0f;

	std::vector<MyRigidBody> m_containedObjects;

	vector3 m_v3Center = vector3(0.0f);
	vector3 m_v3Min = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);

	MyQuadTree* m_pRoot = nullptr;
	std::vector<MyQuadTree*> m_lChild;

public:
	MyQuadTree();
	~MyQuadTree();
};
}

