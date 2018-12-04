#ifndef __MYQUADTREECLASS_H_
#define __MYQUADTREECLASS_H_

#include <vector>
#include "MyRigidBody.h"

namespace Simplex
{
	class MyQuadTree
	{
		uint m_uID = 0;
		uint m_uLevel = 0;

		MyQuadTree* m_pChildren[8];

		float m_fSize = 0.0f;

		std::vector<MyRigidBody*> m_ContainedObjects;

		MyRigidBody* mainQuad;

		vector3 m_v3Center = vector3(0.0f);
		vector3 m_v3Min = vector3(0.0f);
		vector3 m_v3Max = vector3(0.0f);

		MyQuadTree* m_pRoot = nullptr;
		std::vector<MyQuadTree*> m_lChild;

	public:
		void Init();
		void Release();
		void Swap(MyQuadTree & other);
		MyQuadTree(std::vector<MyRigidBody*> rbList);
		MyQuadTree(vector3 center, float size);
		~MyQuadTree();
		MyQuadTree(MyQuadTree const &other);
		MyQuadTree & operator=(MyQuadTree const & other);
		bool IsColliding(MyRigidBody collider);
		void Display();
		void Subdivide();
		bool IsLeaf();
		void ConstructList(int maxLevel, int ideal_Count);
		void KillBranches();
		void AssignID();
		void AnnihilateID();
	};

#endif //__MYQUADTREECLASS_H_
}
