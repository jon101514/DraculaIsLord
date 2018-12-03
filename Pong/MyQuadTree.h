#pragma once
class MyQuadTree
{
public:
	void Init();
	void Delete();
	MyQuadTree();
	~MyQuadTree();
	void IsColliding();
	void Display();
	void Subdivide();
	bool IsLeaf();
	void ConstructList(int maxLevel, int ideal_Count);
	void KillBranches();
};

