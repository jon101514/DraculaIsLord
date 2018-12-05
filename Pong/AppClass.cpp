#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera so that it's focused on the game.
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up
	m_pCameraMngr->SetCameraMode(CAM_ORTHO_Z);
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 16.0f));

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	
	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();
	// Create the first paddle.
	m_pEntityMngr->AddEntity("Pong\\PinkPaddle.obj", m_sP1ID);
	m_v3Player1 = vector3(-10.0f, 0.0f, 0.0f);
	matrix4 m4Position = glm::translate(m_v3Player1);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->GetRigidBody(m_sP1ID)->SetColorColliding(vector3(1.0f));
	
	// Create the second paddle.
	m_pEntityMngr->AddEntity("Pong\\GreenPaddle.obj", m_sP2ID);
	m_v3Player2 = vector3(10.0f, 0.0f, 0.0f);
	m4Position = glm::translate(m_v3Player2);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->GetRigidBody(m_sP2ID)->SetColorColliding(vector3(1.0f));

	// Make the top wall.
	m_pEntityMngr->AddEntity("Pong\\Wall.obj", m_sTWID);
	m_v3TopWall = vector3(0.0f, 15.5f, 0.0f);
	m4Position = glm::translate(m_v3TopWall);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->GetRigidBody(m_sTWID)->SetColorColliding(vector3(1.0f));
	m_pEntityMngr->GetRigidBody(m_sTWID)->AddDimension(0);
	m_pEntityMngr->GetRigidBody(m_sTWID)->AddDimension(1);
	m_pEntityMngr->GetRigidBody(m_sTWID)->AddDimension(2);
	m_pEntityMngr->GetRigidBody(m_sTWID)->AddDimension(3);
	// Make the bottom wall.
	m_pEntityMngr->AddEntity("Pong\\Wall.obj", m_sLWID);
	m_v3LowWall = vector3(0.0f, -13.5f, 0.0f);
	m4Position = glm::translate(m_v3LowWall);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->GetRigidBody(m_sLWID)->SetColorColliding(vector3(1.0f));
	m_pEntityMngr->GetRigidBody(m_sLWID)->AddDimension(0);
	m_pEntityMngr->GetRigidBody(m_sLWID)->AddDimension(1);
	m_pEntityMngr->GetRigidBody(m_sLWID)->AddDimension(2);
	m_pEntityMngr->GetRigidBody(m_sLWID)->AddDimension(3);
	// Set up our Sound Buffers so that we may play sound effects.
	m_sbP1.loadFromFile("FsLo.wav");
	m_sP1.setBuffer(m_sbP1);
	m_sbP2.loadFromFile("FsHi.wav");
	m_sP2.setBuffer(m_sbP2);
	m_sbWall.loadFromFile("Cs.wav");
	m_sWall.setBuffer(m_sbWall);
	m_sbP1Score.loadFromFile("AsLo.wav");
	m_sP1Score.setBuffer(m_sbP1Score);
	m_sbP2Score.loadFromFile("AsHi.wav");
	m_sP2Score.setBuffer(m_sbP2Score);

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

	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(1.0f, 3.0f, 1.0f)); // Scale up our paddles to make them rectanglar.

	// Set up both paddles in the Entity Manager.
	matrix4 mPlayer1 = m4Scale * glm::translate(m_v3Player1) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sP1ID)->SetModelMatrix(mPlayer1);
	m_pEntityMngr->GetRigidBody(m_sP1ID)->SetModelMatrix(mPlayer1);
	m_pMeshMngr->AddAxisToRenderList(mPlayer1);

	matrix4 mPlayer2 = m4Scale * glm::translate(m_v3Player2) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sP2ID)->SetModelMatrix(mPlayer2);
	m_pEntityMngr->GetRigidBody(m_sP2ID)->SetModelMatrix(mPlayer2);
	m_pMeshMngr->AddAxisToRenderList(mPlayer2);

	// Set up both walls in the Entity Manager.
	matrix4 m4WallScale = glm::scale(IDENTITY_M4, vector3(30.0f, 1.0f, 1.0f)); // Now, use a different scale to stretch the walls horizontally.

	matrix4 mTopWall = m4WallScale * glm::translate(m_v3TopWall) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sTWID)->SetModelMatrix(mTopWall);
	m_pEntityMngr->GetRigidBody(m_sTWID)->SetModelMatrix(mTopWall);
	m_pMeshMngr->AddAxisToRenderList(mTopWall);

	matrix4 mLowWall = m4WallScale * glm::translate(m_v3LowWall) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->GetModel(m_sLWID)->SetModelMatrix(mLowWall);
	m_pEntityMngr->GetRigidBody(m_sLWID)->SetModelMatrix(mLowWall);
	m_pMeshMngr->AddAxisToRenderList(mLowWall);

	//Update Entity Manager
	m_pEntityMngr->Update();

	//m_pMeshMngr->AddGridToRenderList(glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
	
	//m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(17.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
		
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);

	bool wasScore = false;
	//display and move the balls
	for (int i = 0; i < m_lBallList.size(); i++)
	{
		m_lBallList[i]->Move(deltaTime);
		wasScore = wasScore || AddScore(m_lBallList[i]); // Check to see if this ball is within either player's scoring zone by passing each ball into AddScore.
		m_lBallList[i]->Display();
	}

	if (resetEnable && wasScore) {
		ResetBalls();

		for (uint i = 0; i < 4; i++)
		{
			quads[i].clear();
		}
	}

	if (winnerEnable) {
		if (m_n1PScore == 3 || m_n2PScore == 3)
		{
			DisplayWinner();
		}
	}

	if (QuadTree) {
		static bool bStarted = false;
		if (m_pSystem->IsTimerDone(uClock) || !bStarted)
		{
			bStarted = true;
			m_pSystem->StartTimerOnClock(.5, uClock);

			for (uint i = 0; i < 4; i++)
			{
				quads[i].clear();
			}

			for (uint i = 0; i < m_lBallList.size(); i++)
			{
				MyRigidBody* rb = m_lBallList[i]->GetRigidBody();

				rb->ClearDimensionList();
				if (rb->GetMaxGlobal().x >= 0.0f && rb->GetMinGlobal().y <= 0) {
					quads[0].push_back(m_lBallList[i]);
				}
				if (rb->GetMaxGlobal().x >= 0.0f && rb->GetMaxGlobal().y >= 0.0f) {
					quads[1].push_back(m_lBallList[i]);
				}
				if (rb->GetMinGlobal().x <= 0.0f && rb->GetMaxGlobal().y >= 0.0f) {
					quads[2].push_back(m_lBallList[i]);
				}
				if (rb->GetMinGlobal().x <= 0.0f && rb->GetMinGlobal().y <= 0.0f) {
					quads[3].push_back(m_lBallList[i]);
				}
			}
		}

		m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(0.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Y));
		m_pMeshMngr->AddGridToRenderList(glm::translate(vector3(0.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X));
	}

	if (!QuadTree) {
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

					float distToMove = 1 - glm::distance(m_lBallList[i]->GetPosition(), m_lBallList[j]->GetPosition());

					movement = glm::normalize(movement) * distToMove;

					m_lBallList[i]->Move(movement);
					m_lBallList[j]->Move(-1 * movement);

					m_lBallList[i]->ChangeDirection(movement);
					m_lBallList[j]->ChangeDirection(-1 * movement);
				}
			}
		}
	}
	else {
		for (uint k = 0; k < 4; k++)
		{
			uint ballCount = quads[k].size();
			// check ball collision with other balls
			for (int i = 0; i < ballCount; i++)
			{
				MyRigidBody* rbI;
				rbI = quads[k][i]->GetRigidBody();

				for (int j = i + 1; j < quads[k].size(); j++)
				{
					MyRigidBody* rbJ = quads[k][j]->GetRigidBody();

					if (rbI->IsCollidingSphere(rbJ))
					{

						vector3 movement = quads[k][i]->GetPosition() - quads[k][j]->GetPosition();

						float distToMove = 1 - glm::distance(quads[k][i]->GetPosition(), quads[k][j]->GetPosition());

						movement = glm::normalize(movement) * distToMove;

						quads[k][i]->Move(movement);
						quads[k][j]->Move(-1 * movement);

						quads[k][i]->ChangeDirection(movement);
						quads[k][j]->ChangeDirection(-1 * movement);
					}
				}
			}
		}
	}

	// Ball : Paddle collisions. Let's check all of the balls against both of the paddles within the same loop.
	// Ball : Wall collisions. Check those within this loop as well.
	for (int i = 0; i < m_lBallList.size(); i++) {
		Ball* currBall = m_lBallList[i]; // This is the current ball we're checking.
		MyRigidBody* player1 = m_pEntityMngr->GetRigidBody(m_sP1ID); // Player 1.
		MyRigidBody* player2 = m_pEntityMngr->GetRigidBody(m_sP2ID); // Player 2.
		MyRigidBody* topWall = m_pEntityMngr->GetRigidBody(m_sTWID); // Top Wall.
		MyRigidBody* lowWall = m_pEntityMngr->GetRigidBody(m_sLWID); // Low Wall.
		MyRigidBody* rbI = currBall->GetRigidBody();

		if (player1->IsColliding(rbI) || player2->IsColliding(rbI)) { // A Player has hit our current ball.
			currBall->ChangeSpeed(); // Also, let's make the ball move a bit faster.
			if (player1->IsColliding(rbI)) { 
				currBall->ChangeDirection(vector3(-1.0f * (currBall->GetDirection().x - 1.0f), currBall->GetDirection().y, currBall->GetDirection().z));
				m_sP1.play(); 
			} else { 
				currBall->ChangeDirection(vector3(-1.0f * (currBall->GetDirection().x + 1.0f), currBall->GetDirection().y, currBall->GetDirection().z));
				m_sP2.play(); 
			}
		}
		if (topWall->IsColliding(rbI) || lowWall->IsColliding(rbI)) { // A ball has contacted a wall.
			m_sWall.play();
			if (topWall->IsColliding(rbI)) {
				currBall->ChangeDirection(vector3(currBall->GetDirection().x, (-1.0f * (currBall->GetDirection().y + 1.0f)), currBall->GetDirection().z));
			} else {
				currBall->ChangeDirection(vector3(currBall->GetDirection().x, (-1.0f * (currBall->GetDirection().y - 1.0f)), currBall->GetDirection().z));
			}
		}
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
	// Release Entity Manager [Memory Management].
	m_pEntityMngr->ReleaseInstance();

	// Release all of the balls.
	for (int i = 0; i < m_lBallList.size(); i++) {
		if (m_lBallList[i] != nullptr) {
			SafeDelete(m_lBallList[i]);
		}
	}
	//release GUI
	ShutdownGUI();
}