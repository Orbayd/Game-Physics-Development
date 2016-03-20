#include <sb6.h>
#include <sb6ktx.h>
#include <math.h>
#include <assert.h>

#include "DebugOut.h"
#include "GameObject.h"
#include "MathEngine.h"
#include "Game.h"
#include "GraphicsObject.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "CameraMan.h"
#include "Image.h"
#include "GameObject2D.h"
#include "Color.h"
#include "Vect2D.h"
#include "ShaderMan.h"
#include "ImageMan.h"
#include "Keyboard.h"
#include "Input.h"
#include "Box2D.h"
#include "PixelToMeter.h"
#include "GameSortBucket.h"
#include "GameObjectName.h"
#include "AngryContactListener.h"
#include "Simulation.h"
#include "Block.h"
#include "BlockFactory.h"
#include "BirdFactory.h"
#include "World.h"
#include "Level.h"
#include "InputTest.h"

#include "TimerMan.h"

#include "CameraDirector.h"
#include "SoundMan.h"

// Global:  todo make a singleton
char buff[256];






//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char* windowName, const int Width, const int Height)
	:Engine(windowName, Width, Height)
{
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	// don't worry we will use this area
	InputMan::Create();
	UnitScale::Create(50.0f);
	Simulation::Create();
	World::Create(0.0, -10.0f);

	// initialize the sound system
	//pSndEngine = irrklang::createIrrKlangDevice();
	SoundManager::Create();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

		Camera *pCam3D = new Camera(Camera::Type::PERSPECTIVE_3D);
		pCam3D->setViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
		pCam3D->setPerspective(50.0f, float(this->screenWidth) / float(this->screenHeight), 0.10f, 1000.0f);

		// Orient Camera
		Vect up3DCam(0.0f, 1.0f, 0.0f);
		Vect pos3DCam(0.0f, 0.0f, 4.0f);
		Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
		pCam3D->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

		// Holder for the current 3D cameras
		CameraMan::SetCurrentCamera(pCam3D, Camera::Type::PERSPECTIVE_3D);

	//---------------------------------------------------------------------------------------------------------
	// Setup the current 2D orthographic Camera
	//---------------------------------------------------------------------------------------------------------

	Camera *pCam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

		pCam2D->setViewport(0, 0, (int)this->screenWidth, (int)this->screenHeight);
		pCam2D->setOrthographic(-pCam2D->getScreenWidth() / 2.0f, pCam2D->getScreenWidth() / 2.0f,
								-pCam2D->getScreenHeight() / 2.0f, pCam2D->getScreenHeight() / 2.0f,
								1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, -1.0f), Vect(0.0f, 0.0f, 0.0f));

		// Holder for the current 2D  cameras
		CameraMan::SetCurrentCamera(pCam2D, Camera::Type::ORTHOGRAPHIC_2D);

	//---------------------------------------------------------------------------------------------------------
	// Load up the managers
	//---------------------------------------------------------------------------------------------------------
	
		// Create/Load Shader 
		ShaderMan::addShader(ShaderName::SPRITE, "../../data/spriteRender");
		ShaderMan::addShader(ShaderName::SPRITE_LINE, "../../data/spriteLineRender");
		ShaderMan::addShader(ShaderName::SPRITE_TRI, "../../data/spriteTriRender");
		ShaderMan::addShader(ShaderName::SPRITE_QUAD, "../../data/spriteQuadRender");

		// Textures
		TextureMan::addTexture("../../data/AngryBirds.tga", TextName::AngryBirds);
		TextureMan::addTexture("../../data/WoodBlocks.tga", TextName::WoodBlocks);
		TextureMan::addTexture("../../data/GlassBlocks.tga", TextName::GlassBlocks);
		TextureMan::addTexture("../../data/woodPlatform.tga", TextName::Platform);
		TextureMan::addTexture("../../data/StoneBlocks.tga", TextName::StoneBlocks);
		TextureMan::addTexture("../../data/AngryBirdBackground.tga", TextName::BackGround);
		TextureMan::addTexture("../../data/AngryBirdBlock.tga", TextName::AdditionalBlocks);
		// Images
		//RubberBand
		ImageMan::addImage(ImageName::RubberBand, TextName::AdditionalBlocks, Rect(473.0f, 557.0f, 192.0f, 32.0f));
		//XLBlock
		ImageMan::addImage(ImageName::BackGround, TextName::BackGround, Rect(0, 0, 1280.0f, 1336.0f));
		ImageMan::addImage(ImageName::Sky, TextName::BackGround, Rect(0, 0, 1280.0f, 446.0f));
		ImageMan::addImage(ImageName::XLWoodBlock, TextName::WoodBlocks, Rect(289.0f, 169.0f, 203.0f, 20.0f));
		//LongBlock
		ImageMan::addImage(ImageName::LongWoodBlock_Healty, TextName::WoodBlocks, Rect(288.0f, 257.0f, 168.0f, 20.0f));
		ImageMan::addImage(ImageName::LongWoodBlock_Minor, TextName::WoodBlocks, Rect(289.0f, 280.0f, 168.0f, 20.0f));
		ImageMan::addImage(ImageName::LongWoodBlock_Moderate, TextName::WoodBlocks, Rect(289.0f, 302.0f, 168.0f, 20.0f));
		ImageMan::addImage(ImageName::LongWoodBlock_NearDead, TextName::WoodBlocks, Rect(289.0f, 324.0f, 168.0f, 20.0f));
		
		//Glass Blocks
		ImageMan::addImage(ImageName::GlassBlock_Healty, TextName::GlassBlocks, Rect(288.0f, 347.0f, 83.0f, 20.0f));
		ImageMan::addImage(ImageName::GlassBlock_Minor, TextName::GlassBlocks, Rect(288.0f, 370.0f, 83.0f, 20.0f));
		ImageMan::addImage(ImageName::GlassBlock_Moderate, TextName::GlassBlocks, Rect(374.0f, 347.0f, 83.0f, 20.0f));
		ImageMan::addImage(ImageName::GlassBlock_NearDead, TextName::GlassBlocks, Rect(374.0f, 370.0f, 83.0f, 20.0f));
		//StoneBlocks
		ImageMan::addImage(ImageName::StoneBlock_Healty, TextName::StoneBlocks, Rect(247.0f, 85.0f, 82.0f, 40.0f));
		ImageMan::addImage(ImageName::StoneBlock_Minor, TextName::StoneBlocks, Rect(332.0f, 85.0f, 82.0f, 40.0f));
		ImageMan::addImage(ImageName::StoneBlock_Moderate, TextName::StoneBlocks, Rect(417, 85.0f, 82.0f, 40.0f));
		ImageMan::addImage(ImageName::StoneBlock_NearDead, TextName::StoneBlocks, Rect(248.0f, 126.0f, 82.0f, 40.0f));
		//StoneBall
		ImageMan::addImage(ImageName::StoneBall_Healty, TextName::StoneBlocks, Rect(169.0f, 82.0f, 75.0f, 75.0f));
		//Piggy
		ImageMan::addImage(ImageName::Piggy_Healty, TextName::AngryBirds, Rect(732.0f, 855.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_HealtyBlink, TextName::AngryBirds, Rect(792.0f, 798.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_HealtySmile, TextName::AngryBirds, Rect(792.0f, 894.0f, 48.0f, 48.0f));

		ImageMan::addImage(ImageName::Piggy_Dmged, TextName::AngryBirds, Rect(732.0f, 903.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_DmgedBlink, TextName::AngryBirds, Rect(793.0f, 847.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_DmgedSmile, TextName::AngryBirds, Rect(936.0f, 743.0f, 48.0f, 48.0f));

		ImageMan::addImage(ImageName::Piggy_HeavyDmged, TextName::AngryBirds, Rect(986.0f, 741.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_HeavyDmgedBlink, TextName::AngryBirds, Rect(853.0f, 797.0f, 48.0f, 48.0f));
		ImageMan::addImage(ImageName::Piggy_HeavyDmgedSmile, TextName::AngryBirds, Rect(853.0f, 844.0f, 48.0f, 48.0f));
		//MediumBlock
		ImageMan::addImage(ImageName::MediumWoodBlock, TextName::WoodBlocks, Rect(289.0f, 345.0f, 81.0f, 20.0f));
		ImageMan::addImage(ImageName::SmallWoodBlock, TextName::WoodBlocks, Rect(458, 257.0f, 40.0f, 20.0f));
		ImageMan::addImage(ImageName::WoodPlatform, TextName::Platform, Rect(0, 0, 156, 44.0));

		ImageMan::addImage(ImageName::GlassTriangle, TextName::GlassBlocks, Rect(85.0f, 169.0f, 84.0f, 84.0f));
		ImageMan::addImage(ImageName::Bang, TextName::AngryBirds, Rect(674.0f, 354.0f, 87.0f, 89.0f));

		ImageMan::addImage(ImageName::SlingshotFront, TextName::AngryBirds, Rect(0.0f, 0.0f, 40, 200));
		ImageMan::addImage(ImageName::SlingshotBack, TextName::AngryBirds, Rect(833.0f, 0.0f, 45, 125));
		//Chunks
		ImageMan::addImage(ImageName::WoodChunk_0, TextName::AngryBirds, Rect(2.0f, 826.0f, 35, 8));
		ImageMan::addImage(ImageName::WoodChunk_1, TextName::AngryBirds, Rect(2.0f, 836.0f, 33, 9));
		ImageMan::addImage(ImageName::WoodChunk_2, TextName::AngryBirds, Rect(13.0f, 848.0f, 21, 6));
		//Smoke
		ImageMan::addImage(ImageName::Smoke, TextName::AngryBirds, Rect(20.0f, 732.0f, 15, 15));
		//RedBird
		ImageMan::addImage(ImageName::RedBird, TextName::AngryBirds, Rect(903.0f, 798.0f, 45.0f, 45.0f));
		ImageMan::addImage(ImageName::RedBirdBlink, TextName::AngryBirds, Rect(956.0f, 845.0f, 50.0f, 42.0f));
		ImageMan::addImage(ImageName::RedBirdSmile, TextName::AngryBirds, Rect(951.0f, 798.0f, 45.0f, 45.0f));
		ImageMan::addImage(ImageName::RedBirdDamaged, TextName::AngryBirds, Rect(853.0f, 892.0f, 45.0f, 45.0f));
		//Red Bird Feathers
		ImageMan::addImage(ImageName::RedFeather, TextName::AngryBirds, Rect(0.0f, 474.0f, 14.0f, 30.0f));
		ImageMan::addImage(ImageName::OrangeFeather, TextName::AngryBirds, Rect(0.0f, 310.0f, 10.0f, 30.0f));
		ImageMan::addImage(ImageName::BrownFeather, TextName::AngryBirds, Rect(10.0f, 274.0f, 10.0f, 30.0f));
		//BlackBird
		ImageMan::addImage(ImageName::BlackBird, TextName::AngryBirds, Rect(410.0f, 725.0f, 60.0f, 80.0f));
		ImageMan::addImage(ImageName::BlackBirdBlink, TextName::AngryBirds, Rect(715.0f, 446.0f, 60.0f, 80.0f));
		ImageMan::addImage(ImageName::BlackBirdSmile, TextName::AngryBirds, Rect(778.0f, 446.0f, 60.0f, 80.0f));

		ImageMan::addImage(ImageName::BlackBirdFly, TextName::AngryBirds, Rect(668.0f, 679.0f, 63.0f, 71.0f));
		
		ImageMan::addImage(ImageName::BlackBirdBombPhase_1, TextName::AngryBirds, Rect(409.0f, 808.0f, 60.0f, 80.0f));
		ImageMan::addImage(ImageName::BlackBirdBombPhase_2, TextName::AngryBirds, Rect(588.0f, 446.0f, 60.0f, 80.0f));
		ImageMan::addImage(ImageName::BlackBirdBombPhase_3, TextName::AngryBirds, Rect(651.0f, 446.0f, 60.0f, 80.0f));
		//YellowBird 
		ImageMan::addImage(ImageName::YellowBird, TextName::AngryBirds, Rect(668.0f, 879.0f, 58.0f, 54.0f));
		ImageMan::addImage(ImageName::YellowBirdBlink, TextName::AngryBirds, Rect(731.0f, 744.0f, 60.0f, 55.0f));
		ImageMan::addImage(ImageName::YellowBirdDamaged, TextName::AngryBirds, Rect(793.0f, 743.0f, 60.0f, 55.0f));
		ImageMan::addImage(ImageName::YellowBirdSmile, TextName::AngryBirds, Rect(731.0f, 800.0f, 60.0f, 55.0f));
		ImageMan::addImage(ImageName::YellowBirdFly, TextName::AngryBirds, Rect(588.0f, 913.0f, 69.0f, 52.0f));
		ImageMan::addImage(ImageName::YellowBirdAbility, TextName::AngryBirds, Rect(864.0f, 745.0f, 68.0f, 52.0f));
		//BlueBird
		ImageMan::addImage(ImageName::BlueBird, TextName::AngryBirds, Rect(0.0f, 379.0f, 32.0f, 30.0f));
		ImageMan::addImage(ImageName::BlueBirdBlink, TextName::AngryBirds, Rect(1.0f, 507.0f, 30.0f, 30.0f));
		ImageMan::addImage(ImageName::BlueBirdSmile, TextName::AngryBirds, Rect(1.0f, 538.0f, 30.0f, 30.0f));
		ImageMan::addImage(ImageName::BlueBirdDamaged, TextName::AngryBirds, Rect(1.0f, 411.0f, 31.0f, 30.0f));
		//WhiteBird
		ImageMan::addImage(ImageName::WhiteBird, TextName::AngryBirds, Rect(410.0f, 353.0f, 80.0f, 95.0f));
		ImageMan::addImage(ImageName::WhiteBirdSmile, TextName::AngryBirds, Rect(410.0f, 543.0f, 80.0f, 95.0f));
		ImageMan::addImage(ImageName::WhiteBirdBlink, TextName::AngryBirds, Rect(410.0f, 448.0f, 80.0f, 95.0f));

		ImageMan::addImage(ImageName::WhiteBirdDamaged, TextName::AngryBirds, Rect(493.0f, 351.0f, 87.0f, 95.0f));
		ImageMan::addImage(ImageName::WhiteBirdUdk, TextName::AngryBirds, Rect(409.0f, 637.0f, 81.0f, 87.0f));

		ImageMan::addImage(ImageName::WhiteBirdAbility, TextName::AngryBirds, Rect(667.0f, 751.0f, 56.0f,68.0f));

		ImageMan::addImage(ImageName::Egg, TextName::AngryBirds, Rect(668.0f, 820.0f, 45.0f, 57.0f));
		//GreenBird
		ImageMan::addImage(ImageName::GreenBird, TextName::AngryBirds, Rect(932.0f, 526.0f, 100.0f, 75.0f));
		ImageMan::addImage(ImageName::GreenBirdBlink, TextName::AngryBirds, Rect(667.0f, 604.0f, 100.0f, 75.0f));
		ImageMan::addImage(ImageName::GreenBirdSmile, TextName::AngryBirds, Rect(827.0f, 528.0f, 102.0f, 72.0f));
		ImageMan::addImage(ImageName::GreenBirdDamaged, TextName::AngryBirds, Rect(950.0f, 604.0f, 95.0f, 72.0f));
		ImageMan::addImage(ImageName::GreenBirdAbility, TextName::AngryBirds, Rect(955.0f, 155.0f, 85.0f, 92.0f));
		//Smoke Explosion
		ImageMan::addImage(ImageName::SmokeExplosion_0, TextName::AngryBirds, Rect(870.0f, 604.0f, 81.0f, 74.0f));
		ImageMan::addImage(ImageName::SmokeExplosion_1, TextName::AngryBirds, Rect(912.0f, 257.0f, 99.0f, 93.0f));
		ImageMan::addImage(ImageName::SmokeExplosion_2, TextName::AngryBirds, Rect(169.0f, 399.0f, 115.0f, 115.0f));
		ImageMan::addImage(ImageName::SmokeExplosion_3, TextName::AngryBirds, Rect(697.0f, 0.0f, 134.0f, 132.0f));
		ImageMan::addImage(ImageName::SmokeExplosion_4, TextName::AngryBirds, Rect(553.0f, 0.0f, 145.0f, 140.0f));
		//Smokes
		ImageMan::addImage(ImageName::SmallSmoke, TextName::AngryBirds, Rect(0.0f, 345.0f, 35.0f, 35.0f));
		ImageMan::addImage(ImageName::SmallSmoke1, TextName::AngryBirds, Rect(20.0f, 731.0f, 17.0f, 17.0f));
		ImageMan::addImage(ImageName::SmallSmoke2, TextName::AngryBirds, Rect(17.0f, 768.0f, 13.0f, 13.0f));
		ImageMan::addImage(ImageName::SmallSmoke3, TextName::AngryBirds, Rect(30.0f, 812.0f, 9.0f, 9.0f));
		//Helmet
		ImageMan::addImage(ImageName::Helmet, TextName::AngryBirds, Rect(956.0f, 889.0f, 82.0f, 38.0f));
		//Stone Chunks
		ImageMan::addImage(ImageName::StoneChunk_0, TextName::AngryBirds, Rect(4.0f, 705.0f, 23.0f, 25.0f));
		ImageMan::addImage(ImageName::StoneChunk_1, TextName::AngryBirds, Rect(4.0f, 569.0f, 34.0f, 30.0f));
		ImageMan::addImage(ImageName::StoneChunk_2, TextName::AngryBirds, Rect(20.0f, 783.0f, 17.0f, 15.0f));
		//Glass Chunks
		ImageMan::addImage(ImageName::GlassChunk_0, TextName::AngryBirds, Rect(5.0f, 203.0f, 26.0f, 33.0f));
		ImageMan::addImage(ImageName::GlassChunk_1, TextName::AngryBirds, Rect(6.0f, 237.0f, 27.0f, 37.0f));
		ImageMan::addImage(ImageName::GlassChunk_2, TextName::AngryBirds, Rect(20.0f, 472.0f, 25.0f, 30.0f));
	//---------------------------------------------------------------------------------------------------------
	// Create Sort Buckets
	//---------------------------------------------------------------------------------------------------------
	
		
	//---------------------------------------------------------------------------------------------------------
	// Create GameObjects
	//---------------------------------------------------------------------------------------------------------
		

		//Level::Level_PI();

		// Level::Level_2PI();
		//Level::Level_PI_Test();
		Level::Level_2PI_Test();
		//Level::Level_3PI_Test();
	//---------------------------------------------------------------------------------------------------------
	// Box2D setup
	//---------------------------------------------------------------------------------------------------------

		// There is only one
		// create and initialize contact listener
		AngryContactListener *myContactListener = new AngryContactListener();
		World::getWorld()->SetContactListener(myContactListener);

		//World::SettleLevel();
		Simulation *pSim = Simulation::Instance();
		pSim->setState(SimulationEnum::Pause);
	/*	pSndTheme = pSndEngine->play2D("../../data/title_theme.mp3", true, false, true);
		assert(pSndTheme);
		pSndTheme->setVolume(0.4f);*/
		
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
AzulStopWatch a;
void Game::Update(float currentTime)
{
	a.tic();

	// Simulation update - sets the time steps
	Simulation::Update();

	// Update cameras - make sure everything is consistent
	//Camera *pCam3D = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
	//pCam3D->updateCamera();

	Camera *pCam2D = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
	pCam2D->updateCamera();

	// Add your update below this line: ----------------------------

	// process input
	
	SimulationInput(0);
	
	//MouseTest();
	

	TimerMan::Update();
	// Physics Update - Step world
	int velocityIterations = 6;
	int positionIternations = 2;
	float timeInSec = Simulation::Instance()->getTimeStep();


	World::getWorld()->Step(timeInSec, velocityIterations, positionIternations);
	

	// Update graphics object
	b2Body *pBody = World::getWorld()->GetBodyList();

	while (pBody != 0)
	{
		GameObject2D *pGameObj = (GameObject2D *)pBody->GetUserData();
		if (pGameObj != 0)
		{
			pGameObj->PhysicsUpdate(pBody->GetPosition(), pBody->GetAngle());
		}
		else
		{
			assert(pGameObj);
		}

		pBody = pBody->GetNext();
	}
	
	
	// update objects
	GameObjectMan::Update(currentTime);

	GameObject2D *pBird = GameObjectMan::getActiveBird();
	Input(pBird);
	//MouseInput(pBird);
	// Do the delete list
	GameObjectMan::DeletePending();	
	
	
	//CameraDirector::Update();

	

}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// draw all objects
	GameObjectMan::Draw();
	a.toc();
	//out("Time spending : %f \n",a.timeInSeconds());
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	// todo fix this.
}

//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
	const GLfloat blue[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, blue);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
