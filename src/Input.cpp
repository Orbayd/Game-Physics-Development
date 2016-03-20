#include <string>
#include "CameraMan.h"
#include "InputMan.h"
#include "Keyboard.h"
#include "DebugOut.h"
#include "Input.h"
#include "PixelToMeter.h"
#include "Simulation.h"
#include "Level.h"
#include "GameObjectMan.h"
#include "GameObject2D.h"

#include "Bird.h"
#include "Ready.h"

#include "Flying.h"
#include "RubberBand.h"
void GetScreenMousePos(float &posX, float &posY)
{
	// get mouse position
	Mouse *mouse = InputMan::GetMouse();

	mouse->GetCursor( posX, posY);

	// correct for origin
	Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
	pCam->CorrectForOrigin(posX, posY);
}

void GetScreenPosition(float &x2, float &y2, float &ratio, Matrix &worldMatrix)
{
	// correct bird for the local screen
	Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);

	Matrix viewMatrix = pCam->getViewMatrix();
	Matrix projMatrix = pCam->getProjMatrix();
	//Matrix worldMatrix = pBird->pGameSprite->getWorld();

	// world * View * projection
	Matrix TransToOriginLowerLeft(TRANS, -pCam->getScreenWidth() / 2.0f, -pCam->getScreenHeight() / 2.0f, 0.0f);
	Vect vout = Vect(0.0f, 0.0f, 0.0f) *  TransToOriginLowerLeft *worldMatrix * viewMatrix * projMatrix;

	ratio = vout[w];

	// make homogeneous
	vout[x] = vout[x] / vout[w];
	vout[y] = vout[y] / vout[w];

	// at this point we have a normalized device coordinates
	// process this through the viewport transformation
	x2 = (vout[x] + 1.0f)*(pCam->getScreenWidth() / 2.0f);
	y2 = (vout[y] + 1.0f)*(pCam->getScreenHeight() / 2.0f);
}


enum PositionState
{
	INSIDE,
	OUTSIDE,
	UNKNOWN
};

enum MouseState
{
	RIGHT = 0x1,
	LEFT = 0x2,
	NONE = 0
};

enum BirdState2
{
	NORMAL,
	MOVING_LEFT_BUTTON,
	MOVING_RIGHT_BUTTON
};

void MouseInput(GameObject2D *pBird)
{
	if (pBird == 0)
		return;
	RubberBand * pRubberBandFront = (RubberBand *)GameObjectMan::Find(GameObjectName::RubberBandFront); pRubberBandFront;
	if (pRubberBandFront == 0)
		return;
	RubberBand * pRubberBandBack = (RubberBand *)GameObjectMan::Find(GameObjectName::RubberBandBack); pRubberBandBack;
	if (pRubberBandBack == 0)
		return;

	b2Body *pBody = pBird->pBody;
	if (pBody == 0)
		return;

	Mouse *mouse = InputMan::GetMouse();
	// Movement control
	MouseState			mState = NONE;
	PositionState		pState = UNKNOWN;
	static	BirdState2	bState = NORMAL;

	// Get the Mouse correct for the origin
		float xPos;
		float yPos;
		GetScreenMousePos(xPos, yPos);

	// ------------------------------------------------------------------
	// Originally Screen and Local are the same, Ratio = 1.0f
	// Get the Bird in local
	// ------------------------------------------------------------------
		float xScreen;
		float yScreen;
		float ratio;
		GetScreenPosition(xScreen, yScreen, ratio, pBird->pGameSprite->getWorld());

	// ----------------------------------------
	// Mouse inside Bird? 
	// ----------------------------------------
		// convert to vectors - easier math
		Vect vMouse(xPos, yPos, 0.0f);
		Vect vLocalScreen(xScreen, yScreen, 0.0f);	

		// Difference in the same reference (Screen)
		Vect vDiff = (vMouse - vLocalScreen);

		// Convert to Local  = Screen -> Local
		vDiff = vDiff * ratio;

		// Local radius is 25.0
		if (vDiff.mag() < 25.0f)
		{
			//out(" INSIDE <---------\n");
			pState = INSIDE;
		}
		else
		{
			//out("                   \n");
			pState = OUTSIDE;
		}


	// --------------------------------------
	// Mouse - button press?
	// --------------------------------------
		mState = NONE;

		if (mouse->GetKeyState(AZUL_MOUSE::BUTTON_RIGHT))
		{
			mState = RIGHT;
		}

		if (mouse->GetKeyState(AZUL_MOUSE::BUTTON_LEFT))
		{
			mState = LEFT;
		}

	// Enter MOVING state
	if (mState == LEFT && pState == INSIDE)
	{
		bState = MOVING_LEFT_BUTTON;
		pBird->pBody->SetActive(false);
	}

	Vect LocalBird(pBird->posX, pBird->posY,0);
	Vect SceneBird(xScreen, yScreen,0);
	Vect LocaltoWord = -LocalBird + SceneBird;

	Vect RubberFrontFixPos(pRubberBandFront->anchorX , pRubberBandFront->anchorY , 0);
	Vect RubberBackFixPos(pRubberBandBack->anchorX , pRubberBandBack->anchorY , 0);
	
	Vect currentPos(vMouse[x] - LocaltoWord[x], vMouse[y] - LocaltoWord[y], 0);
	Vect vectA = RubberFrontFixPos - currentPos  ;
	Vect VectB = RubberBackFixPos - currentPos ;

	//Vect vectA = RubberFrontFixPos - currentPos+ LocaltoWord;
	//Vect VectB = RubberBackFixPos - currentPos+ LocaltoWord;
	//out("\n");
	//out("Mouse: %4.2f %4.2f \n", xPos, yPos);
	//out("\n");
	//out("         Bird: %4.2f %4.2f \n", pBird->posX, pBird->posY);
	//out("\n");
	//out(" Screen: %4.2f %4.2f  <--- \n", xScreen, yScreen);
	////out("Diff %f, %f" , vDiff[x], vDiff[y]);
	//out("\n");
	//out(" vout[w]:  %f \n", ratio);
	//// Anchor and max

	if (bState == MOVING_LEFT_BUTTON){
		float maxLength = 70.0f;
		if (vectA.mag() > maxLength)
		{

			// Adjust B to maxLength
			vectA.norm();
			vectA *= maxLength;// *Level::getScale();
			currentPos = RubberFrontFixPos - vectA;
			//out(" x: %f y: %f,", currentPos[x], currentPos[y]);
			VectB.norm();
			VectB *= maxLength;//* Level::getScale();


		}
	}
	// small sublty here, once moving, left dictates mode
	if (bState == MOVING_LEFT_BUTTON)
	{

		if (mState == LEFT)
		{
			pBody->SetActive(false);
			//pBody->SetActive(true);
		}
		if (mouse->IsReleased(AZUL_MOUSE::BUTTON_LEFT))
		{

			//pBird->pBody->SetGravityScale(1.0f);

			float speed = vectA.mag();
			speed *= Level::getScale();
			b2Vec2 angle(vectA[x], vectA[y]);

			angle.Normalize();
			b2Vec2 vel = speed * angle;

			out("Velocity:(%f,%f) \n", vel.x, vel.y);
			out("Speed:(%f) \n", speed);
			pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			pBody->SetActive(true);
			pBody->ApplyLinearImpulse(vel, pBody->GetWorldCenter(), true);



			bState = NORMAL;

			Vect verts[4];
			verts[0] = Vect(0, 0, 0);
			verts[1] = Vect(0, 0, 0);
			verts[2] = Vect(0, 0, 0);
			verts[3] = Vect(0, 0, 0);
			GraphicsObject_Quad*pGraphics_Quad_Back = (GraphicsObject_Quad*)pRubberBandFront->getGraphicsObject();
			pGraphics_Quad_Back->setVects(verts);

			GraphicsObject_Quad*pGraphics_Quad_Front = (GraphicsObject_Quad*)pRubberBandBack->getGraphicsObject();
			pGraphics_Quad_Front->setVects(verts);

			if (vel.Length()>10.0f)
			{
				Bird* p = (Bird*)pBird;
				p->ChangeState(Fly::GetInstance());
				
			}
			else
			{
				pBird->pBody->SetActive(false);
				Bird* p = (Bird*)pBird;
				p->ChangeState(Ready::GetInstance());
			}

		}
		else
		{
			Vect Perp(-vectA[y], vectA[x], 0);
			Perp.norm();
			Perp *= 5.0f;//::getScale() ;

			Vect verts[4];
			verts[0] = RubberFrontFixPos - Perp;
			verts[1] = currentPos - Perp ;
			verts[2] = currentPos + Perp ;
			verts[3] = RubberFrontFixPos + Perp;
			GraphicsObject_Quad*pGraphics_Quad_Front = (GraphicsObject_Quad*)pRubberBandFront->getGraphicsObject();
			pGraphics_Quad_Front->setVects(verts);



			Vect PerpFront(-VectB[y], VectB[x], 0);
			PerpFront.norm();
			PerpFront *= 5.0f;//* Level::getScale();

			Vect vertsFront[4];
			vertsFront[0] = RubberBackFixPos - PerpFront;
			vertsFront[1] = currentPos - PerpFront ;
			vertsFront[2] = currentPos + PerpFront ;
			vertsFront[3] = RubberBackFixPos + PerpFront;
			GraphicsObject_Quad*pGraphics_Quad_Back = (GraphicsObject_Quad*)pRubberBandBack->getGraphicsObject();
			pGraphics_Quad_Back->setVects(vertsFront);

			pBody->SetTransform(b2Vec2(PixelToMeter(currentPos[x]), PixelToMeter(currentPos[y])), 0);




		}
	}

}





// --- Simulation controls ------------
//   <space> - single step
//   D		 - repeat step while holding
//   G       - start simulation fixed step
//   H       - start simulation realtime stepping
//   R       - reset bird to left

void SimulationInput(GameObject2D *)
{
	// ------------------------------------------------------------------
	//  SIMULATION Controls 
	// ------------------------------------------------------------------
	static int oldKey = 0;

	Simulation *pSim = Simulation::Instance();
	Keyboard *key = InputMan::GetKeyboard();

		if (key->GetKeyState(AZUL_KEY::KEY_G))
		{
			pSim->setState(SimulationEnum::FixedStep);
		}
		else if (key->GetKeyState(AZUL_KEY::KEY_H))
		{
			pSim->setState(SimulationEnum::Realtime);
		}

		if ( key->GetKeyState(AZUL_KEY::KEY_SPACE) && (oldKey == 0))
		{
			// Do only once "a single step"
			pSim->setState(SimulationEnum::SingleStep);
		}

		if (key->GetKeyState(AZUL_KEY::KEY_D))
		{
			// repeating "a single step"
			pSim->setState(SimulationEnum::SingleStep);
		}
	

	oldKey = key->GetKeyState(AZUL_KEY::KEY_SPACE);

}

void Input(GameObject2D *pBird )
{

	//------------------------------------------------------------------------
	// get keyboard
	//------------------------------------------------------------------------

	Keyboard *key = InputMan::GetKeyboard();



	// Quick and dirty test, if these work the rest do.
	// ---> try a,s,d,<SPACE> keys
	if (pBird)
	{
		//if (key->GetKeyState(AZUL_KEY::KEY_SPACE))
		//{
		//	// reset
		//	b2Vec2 pos(PixelToMeter(300.0f), PixelToMeter(500.0f));
		//	pBird->pBody->SetTransform(pos, 0.0f);
		//	b2Vec2 clear(0, 0);
		//	pBird->pBody->ApplyLinearImpulse(clear, pBird->pBody->GetWorldCenter(), true);
		//	pBird->pBody->SetActive(false);
		//	pBird->pBody->SetAngularVelocity(0.0f);
		//	pBird->pBody->SetLinearVelocity(clear);

		//	pBird->pBody->SetActive(false);

		//}
		//else if (key->GetKeyState(AZUL_KEY::KEY_G))
		//{
		//	pBird->pBody->SetActive(true);
		//}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_PERIOD))
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		
		
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);

		pos += dir * 0.11f;
		/*if (pos[z] < 1.12f)*/
		{
			//out("%f %f \n", pos.X(), pos.Y());
			pCam->setOrientAndPosition(up, lookAt, pos);
		}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_COMMA) )
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);

		pos -= dir * 0.11f;
		// make sure pos is greater than lookAt along dir direction
		// otherwise its inside out and breaks
		if ((pos - lookAt).dot(dir) > 0.02f)
		{
			if (pos[z] > 0.020f)
			{
				pCam->setOrientAndPosition(up, lookAt, pos);
			}
		}
		else
		{
			pos += dir * 0.11f;
		}
	}


	if (key->GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;
		Vect right;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);
		pCam->getRight(right);
		
		if (pos[x] <  1280-130)
		{

			pos += right * 10.0f;
			lookAt += right * 10.0f;

			pCam->setOrientAndPosition(up, lookAt, pos);

		}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;
		Vect right;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);
		pCam->getRight(right);

		if (pos[x] > 600 - 1280 * 0.5f){

			pos -= right * 10.0f;
			lookAt -= right * 10.0f;
			pCam->setOrientAndPosition(up, lookAt, pos);
		}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;
		Vect right;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);
		pCam->getRight(right);
		if (pos[y] <  1336.0f *0.25f -250)
		{
			pos += up * 10.0f;
			lookAt += up * 10.0f;

			pCam->setOrientAndPosition(up, lookAt, pos);
		}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect pos;
		Vect dir;
		Vect lookAt;
		Vect up;
		Vect right;

		pCam->getPos(pos);
		pCam->getDir(dir);
		pCam->getLookAt(lookAt);
		pCam->getUp(up);
		pCam->getRight(right);
		if (pos[y] > 250 - 1336.0f *0.25f)
		{
			pos -= up * 10.0f;
			lookAt -= up * 10.0f;

			pCam->setOrientAndPosition(up, lookAt, pos);
		}
	}

	if (key->GetKeyState(AZUL_KEY::KEY_Q))
	{
		// move the camera to center of bird, do not affect zoom
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		Vect initalPos;
		Vect pos;
		Vect lookAt;
		Vect initalLookAt;
		pCam->getPos(initalPos);
		pCam->getLookAt(initalLookAt);
		if (pBird->posX >= 600 - 1280 * 0.5f && pBird->posX < 300+ 1280 +1280*0.5f && pBird->posY < 1366 *0.5f +300)
		{
			pCam->TargetWorldScreen(pos, lookAt, pBird->posX, pBird->posY);
			Vect up;
			pCam->getUp(up);
			pCam->setOrientAndPosition(up, lookAt, pos);
			out("Bird Position %f, %f \n", pBird->posX, pBird->posY);
			out("Camera Position %f, %f \n", pos[x], pos[y]);
		}
		else{

			Vect up;
			pCam->getUp(up);
			//pCam->TargetWorldScreen(pos, lookAt, initalPos[x], initalPos[y]);
			pCam->setOrientAndPosition(up, initalLookAt, initalPos);
			out("Inital  Camera Position %f, %f \n", 0, 0);
		}
	}
	if (key->GetKeyState(AZUL_KEY::KEY_1))
	{
		if (Level::getActive() != LevelName::LEVEL_1){
			GameObjectMan::Clear();
			Level::Level_PI_Test();


		}

	}

	if (key->GetKeyState(AZUL_KEY::KEY_2))
	{
		if (Level::getActive() != LevelName::LEVEL_2){
			GameObjectMan::Clear();

			Level::Level_2PI_Test();

		}

	}
	if (key->GetKeyState(AZUL_KEY::KEY_3))
	{
		if (Level::getActive() != LevelName::LEVEL_3){
			GameObjectMan::Clear();

			Level::Level_3PI_Test();

		}

	}
	if (key->GetKeyState(AZUL_KEY::KEY_R))
	{

		GameObjectMan::Clear();
		if (Level::getActive() == LevelName::LEVEL_1)
		{
			Level::Level_PI_Test();
		}
		else
			Level::Level_2PI_Test();

	}


}

