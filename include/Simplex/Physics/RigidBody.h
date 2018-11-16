/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __RIGIDBODY_H_
#define __RIGIDBODY_H_

#include "Simplex\Mesh\Model.h"

namespace Simplex
{
enum eSATResults
{
	SAT_NONE = 0,
	
	SAT_AX,
	SAT_AY,
	SAT_AZ,

	SAT_BX,
	SAT_BY,
	SAT_BZ,

	SAT_AXxBX,
	SAT_AXxBY,
	SAT_AXxBZ,

	SAT_AYxBX,
	SAT_AYxBY,
	SAT_AYxBZ,

	SAT_AZxBX,
	SAT_AZxBY,
	SAT_AZxBZ,
};

//System Class
class SimplexDLL RigidBody
{
public:
	typedef RigidBody* PRigidBody; //Entity Pointer

protected:
	MeshManager* m_pMeshMngr = nullptr; //for displaying the Rigid Body

	bool m_bVisibleBS = false; //Visibility of bounding sphere
	bool m_bVisibleOBB = true; //Visibility of Oriented bounding box
	bool m_bVisibleARBB = true; //Visibility of axis (Re)aligned bounding box

	float m_fRadius = 0.0f; //Radius

	vector3 m_v3ColorColliding = C_RED; //Color when colliding
	vector3 m_v3ColorNotColliding = C_WHITE; //Color when not colliding

	vector3 m_v3CenterL = ZERO_V3; //center point in local space
	vector3 m_v3CenterG = ZERO_V3; //center point in global space

	vector3 m_v3MinL = ZERO_V3; //minimum coordinate in local space (for OBB)
	vector3 m_v3MaxL = ZERO_V3; //maximum coordinate in local space (for OBB)

	vector3 m_v3MinG = ZERO_V3; //minimum coordinate in global space (for ARBB)
	vector3 m_v3MaxG = ZERO_V3; //maximum coordinate in global space (for ARBB)

	vector3 m_v3HalfWidth = ZERO_V3; //half the size of the Oriented Bounding Box
	vector3 m_v3ARBBSize = ZERO_V3;// size of the Axis (Re)Alligned Bounding Box

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate

	uint m_uCollidingCount = 0; //size of the colliding set
	PRigidBody* m_CollidingArray = nullptr; //array of rigid bodies this one is colliding with

public:
	/*
	Usage: Constructor
	Arguments: std::vector<vector3> a_pointList -> list of points to make the Rigid Body for
	Output: class object instance
	*/
	RigidBody(std::vector<vector3> a_pointList);
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	RigidBody(RigidBody const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	RigidBody& operator=(RigidBody const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~RigidBody(void);
	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	void Swap(RigidBody& other);

	/*
	USAGE: Will render the Rigid Body at the model to world matrix
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddToRenderList(void);

	/*
	USAGE: Clears the colliding list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearCollidingList(void);

	/*
	USAGE: Mark collision with the incoming Rigid Body
	ARGUMENTS: RigidBody* other -> inspected rigid body
	OUTPUT: ---
	*/
	void AddCollisionWith(RigidBody* other);

	/*
	USAGE: Remove marked collision with the incoming Rigid Body
	ARGUMENTS: RigidBody* other -> inspected rigid body
	OUTPUT: ---
	*/
	void RemoveCollisionWith(RigidBody* other);

	/*
	USAGE: Tells if the object is colliding with the incoming one
	ARGUMENTS: RigidBody* const other -> inspected rigid body
	OUTPUT: are they colliding?
	*/
	bool IsColliding(RigidBody* const other);
#pragma region Accessors
	/*
	Usage: Gets visibility of bounding sphere
	Arguments: ---
	Output: visibility
	*/
	bool GetVisibleBS(void);
	/*
	Usage: Sets visibility of bounding sphere
	Arguments: bool a_bVisibility -> visibility to set
	Output: ---
	*/
	void SetVisibleBS(bool a_bVisibility);
	/*
	Usage: Gets visibility of oriented bounding box
	Arguments: ---
	Output: visibility
	*/
	bool GetVisibleOBB(void);
	/*
	Usage: Sets visibility of oriented bounding box
	Arguments: bool a_bVisibility -> visibility to set
	Output: ---
	*/
	void SetVisibleOBB(bool a_bVisibility);
	/*
	Usage: Gets visibility of axis (re)aligned bounding box
	Arguments: ---
	Output: visibility
	*/
	bool GetVisibleARBB(void);
	/*
	Usage: Sets visibility of axis (re)aligned bounding box
	Arguments: bool a_bVisibility -> visibility to set
	Output: ---
	*/
	void SetVisibleARBB(bool a_bVisibility);
	/*
	Usage: Gets radius
	Arguments: ---
	Output: radius
	*/
	float GetRadius(void);
	/*
	Usage: Gets the color when colliding
	Arguments: ---
	Output: color
	*/
	vector3 GetColorColliding(void);
	/*
	Usage: Sets the color when colliding
	Arguments: vector3 a_v3Color -> color
	Output: ---
	*/
	void SetColorColliding(vector3 a_v3Color);
	/*
	Usage: Gets the color when not colliding
	Arguments: ---
	Output: color
	*/
	vector3 GetColorNotColliding(void);
	/*
	Usage: Sets the color when colliding
	Arguments: vector3 a_v3Color -> color
	Output: ---
	*/
	void SetColorNotColliding(vector3 a_v3Color);
	/*
	Usage: Gets center in local space
	Arguments: ---
	Output: center
	*/
	vector3 GetCenterLocal(void);
	/*
	Usage: Gets minimum vector in local space
	Arguments: ---
	Output: min vector
	*/
	vector3 GetMinLocal(void);
	/*
	Usage: Gets maximum vector in local space
	Arguments: ---
	Output: max vector
	*/
	vector3 GetMaxLocal(void);
	/*
	Usage: Gets center in global space
	Arguments: ---
	Output: center
	*/
	vector3 GetCenterGlobal(void);
	/*
	Usage: Gets minimum vector in global space
	Arguments: ---
	Output: min vector
	*/
	vector3 GetMinGlobal(void);
	/*
	Usage: Gets max vector in global space
	Arguments: ---
	Output: max vector
	*/
	vector3 GetMaxGlobal(void);
	/*
	Usage: Gets the size of the model divided by 2
	Arguments: ---
	Output: halfwidth vector
	*/
	vector3 GetHalfWidth(void);
	/*
	Usage: Gets Model to World matrix
	Arguments: ---
	Output: model to world matrix
	*/
	matrix4 GetModelMatrix(void);
	/*
	Usage: Sets Model to World matrix
	Arguments: Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ModelMatrix);
	/*
	USAGE: Gets the array of rigid bodies pointer this one is colliding with
	ARGUMENTS: ---
	OUTPUT: list of colliding rigid bodies
	*/
	PRigidBody* GetColliderArray(void);
	/*
	USAGE: Returns the number of objects colliding with this one
	ARGUMENTS: ---
	OUTPUT: colliding count
	*/
	uint GetCollidingCount(void);
#pragma endregion
	/*
	USAGE: Checks if the input is in the colliding array
	ARGUMENTS: RigidBody* a_pEntry -> Entry queried
	OUTPUT: is it in the array?
	*/
	bool IsInCollidingArray(RigidBody* a_pEntry);
	
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
	/*
	USAGE: This will apply the Separation Axis Test
	ARGUMENTS: RigidBody* const a_pOther -> other rigid body to test against
	OUTPUT: 0 for colliding, all other first axis that succeeds test
	*/
	uint SAT(RigidBody* const a_pOther);
};//class

//EXPIMP_TEMPLATE template class SimplexDLL std::vector<RigidBody>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<RigidBody*>;

} //namespace Simplex

#endif //__MYRIGIDBODY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/