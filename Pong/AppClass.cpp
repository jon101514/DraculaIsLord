#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	
	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();
	// Create the first object.
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", m_sP1ID);
	m_v3Player1 = vector3(-10.0f, 0.0f, 0.0f);
	matrix4 m4Position = glm::translate(m_v3Player1);
	m_pEntityMngr->SetModelMatrix(m4Position);
	
	// Create the second object.
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", m_sP2ID);
	m_v3Player2 = vector3(10.0f, 0.0f, 0.0f);
	m4Position = glm::translate(m_v3Player2);
	m_pEntityMngr->SetModelMatrix(m4Position);
	// Commented this out so that it doesn't generate 500 squares.
	/*
	uint uInstances = 500;
	int nSquare = static_cast<int>(std::sqrt(uInstances));
	uInstances = nSquare * nSquare;
	
	uint uIndex = 0;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 0; j < nSquare; j++)
		{
			m_pEntityMngr->AddEntity("Minecraft\\Cube.obj");
			vector3 v3Position = vector3(glm::sphericalRand(34.0f));
			matrix4 m4Position = glm::translate(v3Position);
			m_pEntityMngr->SetModelMatrix(m4Position);
			//m_pEntityMngr->AddDimension(-1, uIndex);
			//++uIndex;
			
			if (v3Position.x < 0.0f)
			{
				if (v3Position.x < -17.0f)
					m_pEntityMngr->AddDimension(-1, 1);
				else
					m_pEntityMngr->AddDimension(-1, 2);
			}
			else if (v3Position.x > 0.0f)
			{
				if (v3Position.x > 17.0f)
					m_pEntityMngr->AddDimension(-1, 3);
				else
					m_pEntityMngr->AddDimension(-1, 4);
			}
			
		}
	}
	*/
	m_pEntityMngr->Update();
	//steve
	//m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
}
void Application::Update(void)
{

	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	float deltaTime = m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	matrix4 mPlayer1 = glm::translate(m_v3Player1) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sP1ID)->SetModelMatrix(mPlayer1);
	m_pEntityMngr->GetRigidBody(m_sP1ID)->SetModelMatrix(mPlayer1);
	m_pMeshMngr->AddAxisToRenderList(mPlayer1);

	matrix4 mPlayer2 = glm::translate(m_v3Player2) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sP2ID)->SetModelMatrix(mPlayer2);
	m_pEntityMngr->GetRigidBody(m_sP2ID)->SetModelMatrix(mPlayer2);
	m_pMeshMngr->AddAxisToRenderList(mPlayer2);

	

	//Update Entity Manager
	m_pEntityMngr->Update();

	m_pMeshMngr->AddGridToRenderList(glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
	m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(-17.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
	m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(17.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
		
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);

	//display and move the balls
	for (int i = 0; i < m_lBallList.size(); i++)
	{
		m_lBallList[i]->Move(deltaTime);
		m_lBallList[i]->Display();
	}

	// check ball collision with other balls
	for (int i = 0; i < m_lBallList.size(); i++)
	{
		MyRigidBody* rbI;
		rbI = m_lBallList[i]->GetRigidBody();

		for (int j = i + 1; j < m_lBallList.size(); j++)
		{
			MyRigidBody* rbJ = m_lBallList[j]->GetRigidBody();

			if (rbI->IsCollidingSphere(rbJ)) 
			{
				
				vector3 movement = m_lBallList[i]->GetPosition() - m_lBallList[j]->GetPosition();

				float distToMove = 2 - glm::distance(m_lBallList[i]->GetPosition(), m_lBallList[j]->GetPosition());

				movement = glm::normalize(movement) * distToMove;

				m_lBallList[i]->Move(movement);
				m_lBallList[j]->Move(-1 * movement);


				vector3 temp = m_lBallList[i]->GetDirection();
				m_lBallList[i]->ChangeDirection(m_lBallList[j]->GetDirection());
				m_lBallList[j]->ChangeDirection(temp);
			}
		}
	}

	// check collision with player 1 paddle
	for (int i = 0; i < m_lBallList.size(); i++)
	{
		MyRigidBody* player1 = m_pEntityMngr->GetRigidBody(m_sP1ID);
		MyRigidBody* rbI = m_lBallList[i]->GetRigidBody();

		player1->IsColliding(rbI);
	}

	// check collision with player 2 paddle
	for (int i = 0; i < m_lBallList.size(); i++)
	{
		MyRigidBody* player2 = m_pEntityMngr->GetRigidBody(m_sP2ID);
		MyRigidBody* rbI = m_lBallList[i]->GetRigidBody();

		//player2->IsColliding(rbI);
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}