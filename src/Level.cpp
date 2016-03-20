#include "Level.h"
#include "Box2D.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "BlockFactory.h"
#include "BirdFactory.h"
#include "WoodPlatfomFactory.h"
#include "GameObjectMan.h"
#include "BackGroundFactory.h"
#include "SlingShotFactory.h"
#include "PixelToMeter.h"
#include "PiggyFactory.h"
#include "RubberBand.h"

#include "BlackBird.h"
#include "YellowBird.h"
#include "BlueBird.h"
#include "WhiteBird.h"
#include "GreenBird.h"
#include "RedBird.h"
#include "StoneBall.h"
#include "Ready.h"
#include "CameraMan.h"
#include "StoneBlock.h"
#include "ThreadMill.h"
#include "HelmetPiggy.h"
void Level::Level_PI()
{
	GameSortBucket *pSortBlocks;

	pSortBlocks = new GameSortBucket(GameObjectName::Blocks_Sort);
	GameObjectMan::Add(pSortBlocks);

	
	// add bucket group



	// Bottom static
	GameObject *pObj = BlockFactory::Create(GameObjectName::L1_BottomBlock, ImageName::LongWoodBlock_Healty, Rect(400, 20, 400, 20), 0, b2BodyType::b2_staticBody);
	assert(pObj);

	// Dynamic {right,left,top}
	BlockFactory::Create(GameObjectName::L1_RightBlock, ImageName::LongWoodBlock_Healty, Rect(500, 50 + (20 + 10) + 10, 20, 100), 0);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(300, 50 + (20 + 10) + 10, 20, 100), 0);
	BlockFactory::Create(GameObjectName::L1_TopBlock, ImageName::LongWoodBlock_Healty, Rect(400, 100 + (20 + 10) + 25, 250, 20), 0);


}

void Level::Level_2PI()
{
	// add bucket group
	GameSortBucket *pSortBlocks;

	pSortBlocks = new GameSortBucket(GameObjectName::Blocks_Sort);
	GameObjectMan::Add(pSortBlocks);


	// Bottom static
	BlockFactory::Create(GameObjectName::L2_BottomBlock, ImageName::LongWoodBlock_Healty, Rect(400, 20, 500, 20), 0, b2BodyType::b2_staticBody);

	// Dynamic {right,left,top}
	BlockFactory::Create(GameObjectName::L2_LeftRightBlock, ImageName::LongWoodBlock_Healty, Rect(300, 50 + (20 + 10) + 10, 20, 100));
	BlockFactory::Create(GameObjectName::L2_LeftLeftBlock, ImageName::LongWoodBlock_Healty, Rect(350, 50 + (20 + 10) + 10, 20, 100));
	BlockFactory::Create(GameObjectName::L2_TopLeftBlock, ImageName::LongWoodBlock_Healty, Rect(325, 100 + (20 + 10) + 25, 125, 20));

	BlockFactory::Create(GameObjectName::L2_RightRightBlock, ImageName::LongWoodBlock_Healty, Rect(500, 50 + (20 + 10) + 10, 20, 100));
	BlockFactory::Create(GameObjectName::L2_RightLeftBlock, ImageName::LongWoodBlock_Healty, Rect(550, 50 + (20 + 10) + 10, 20, 100));
	BlockFactory::Create(GameObjectName::L2_TopRightBlock, ImageName::LongWoodBlock_Healty, Rect(525, 100 + (20 + 10) + 25, 125, 20));

}

void Level::Level_PI_Test()
{


	Level * l = Level::privGetInstance(); 
	l->active = LevelName::LEVEL_1;
	l->scalefactor = 1.00f;

	GameObjectMan::CreateSorting();
	Vect Pivot(1200.0f, 70.0f, 0.0f);
	Vect A(150.0f, 150.0f, 0.0f);
	SlingShotFactory::Create(A);
	
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300, 300, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280, 295, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 - 1280, 305, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280+900, 295, 1280, 1336));

	
	YellowBird::Create(GameObjectName::L1_RedBird, ImageName::YellowBird, Rect(A[X] + 170, A[Y] - 65, 58.0f * Level::getScale(), 54.0f* Level::getScale()));
	YellowBird::Create(GameObjectName::L1_RedBird, ImageName::YellowBird, Rect(A[X] + 120, A[Y] - 65, 58.0f * Level::getScale(), 54.0f* Level::getScale()));
	
	BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] - 100, A[Y] - 65, 32.0f * Level::getScale(), 30.0f* Level::getScale()));
	BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] - 150, A[Y] - 65, 32.0f * Level::getScale(), 30.0f* Level::getScale()));
    BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] - 200, A[Y] - 65, 32.0f * Level::getScale(), 30.0f* Level::getScale()));
	
	RedBird::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(A[X] + 20, A[Y] - 65 , 45.0f * Level::getScale(), 45.0f* Level::getScale()));
	Bird *pBlue = RedBird::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(A[X] + 70, A[Y] -65, 45.0f * Level::getScale(), 45.0f* Level::getScale()));
	GameObjectMan::setActiveBird(pBlue);

	
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x], Pivot[y] + 290, 50.0f * Level::getScale(), 50.0f* Level::getScale()));

	PlatformFactory::Create(GameObjectName::Platform_1, ImageName::WoodPlatform, Rect(Pivot[x] + 156 * 0.5f, Pivot[y], 156 , 44 ));
	PlatformFactory::Create(GameObjectName::Platform_2, ImageName::WoodPlatform, Rect(Pivot[x] - 156 * 0.5f, Pivot[y], 156 , 44 ));
	
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] - 75, Pivot[y] + 125, 203 , 20 ), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] + 75, Pivot[y] + 125, 203  , 20  ), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 235, 168, 20), 0 * DEGTORAD);

	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] - 40, Pivot[y] + 345, 203 , 20 ), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] + 40, Pivot[y] + 345, 203 , 20 ), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 460, 80 , 20 ), 0 * DEGTORAD);

	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] - 145, Pivot[y] + 40, 40 , 20 ), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x] + 145, Pivot[y] + 40, 40 , 20), 90 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 250, 40 , 20 ), 0 * DEGTORAD);
	BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 490, 40 , 20 ), 90 * DEGTORAD);

	 BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 33, 80 , 20 ), 0 * DEGTORAD);
	 BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::GlassBlock_Healty, Rect(Pivot[x] + 30, Pivot[y] + 83, 80 , 20 ), -90 * DEGTORAD);
	 BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::GlassBlock_Healty, Rect(Pivot[x] - 30, Pivot[y] + 83, 80, 20 ), -90 * DEGTORAD);
	  BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(Pivot[x], Pivot[y] + 135.5f, 80 , 20 ), 0 * DEGTORAD);

	


	


}
void Level::Level_2PI_Test()
{
	Level * l = Level::privGetInstance();
	l->active = LevelName::LEVEL_2;
	l->scalefactor = 1.0f;

	Vect MainPivot(1500.0f, 80.0f, 0.0f);
	Vect LeftPivot(MainPivot[x] - 100, MainPivot[y] - 10, 0.0f);
	Vect RightPivot(MainPivot[x] + 100, MainPivot[y] - 10, 0.0f);
	GameObjectMan::CreateSorting();
	//BackGround//
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300, 300, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280, 295, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 - 1280, 305, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280 + 900, 295, 1280, 1336));


	//SlingShot
	Vect A(125.0f, 150.0f, 0.0f);
	SlingShotFactory::Create(A);

	BlackBird::Create(GameObjectName::L1_RedBird, ImageName::BlackBird, Rect(A[X] + 100, A[Y] - 35, 60.0f * Level::getScale(), 80.0f* Level::getScale()));
	BlackBird::Create(GameObjectName::L1_RedBird, ImageName::BlackBird, Rect(A[X] - 100, A[Y] - 35, 60.0f * Level::getScale(), 80.0f* Level::getScale()));
	
	GreenBird::Create(GameObjectName::L1_RedBird, ImageName::GreenBird, Rect(A[X] + 180, A[Y] - 45, 100.0f * Level::getScale(), 75.0f* Level::getScale()));
	GreenBird::Create(GameObjectName::L1_RedBird, ImageName::GreenBird, Rect(A[X] - 180, A[Y] - 45, 100.0f * Level::getScale(), 75.0f* Level::getScale()));
	
	
	WhiteBird::Create(GameObjectName::L1_RedBird, ImageName::WhiteBird, Rect(A[X] + 250, A[Y] - 45, 85.0f * Level::getScale(), 95.0f* Level::getScale())); 
	WhiteBird::Create(GameObjectName::L1_RedBird, ImageName::WhiteBird, Rect(A[X] - 250, A[Y] - 45, 85.0f * Level::getScale(), 95.0f* Level::getScale())); 
	
	Bird * pBlue = GreenBird::Create(GameObjectName::L1_RedBird, ImageName::GreenBird, Rect(A[X] + 180, A[Y] - 45, 100.0f * Level::getScale(), 75.0f* Level::getScale()));
	GameObjectMan::setActiveBird(pBlue);
	
	//Birds
	//RedBird::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(A[X] + 120, A[Y] - 45, 45.0f * Level::getScale(), 45.0f* Level::getScale()));
	//YellowBird::Create(GameObjectName::L1_RedBird, ImageName::YellowBird, Rect(A[X] + 80, A[Y] - 45, 58.0f * Level::getScale(), 54.0f* Level::getScale()));
	//BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] + 100, A[Y] - 65, 32.0f * Level::getScale()* 0.8f, 30.0f* Level::getScale()* 0.8f));
	//BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] + 250, A[Y] - 65, 32.0f * Level::getScale()* 0.8f, 30.0f* Level::getScale()* 0.8f));
	//Bird * pBlue = BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] + 150, A[Y] - 65, 32.0f * Level::getScale(), 30.0f* Level::getScale()));
	

	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(850+500, 305, 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(850 + 800, 305, 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(850 + 650, 130, 50.0f * Level::getScale()*1.5f, 50.0f* Level::getScale()*1.5f));
	//Middle
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(MainPivot[x], MainPivot[y] + 20, 168, 20), 0, b2BodyType::b2_dynamicBody);
	//FloorLvl
	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(LeftPivot[x], LeftPivot[y], 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_staticBody);
	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(LeftPivot[x] - 85, LeftPivot[y], 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_staticBody);
	//1UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 70, LeftPivot[y] + 40, 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 5, LeftPivot[y] + 40, 20 * 2, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	//2UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 30, LeftPivot[y] + 82, 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 91, LeftPivot[y] + 82, 20 * 2, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	//3UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x], LeftPivot[y] + 145, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 100, LeftPivot[y] + 145, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(LeftPivot[x] - 50, LeftPivot[y] + 145, 80, 20 * 2), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//4UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 50, LeftPivot[y] + 190, 168, 20), 0, b2BodyType::b2_dynamicBody);
	//5UP
	
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] + 10, LeftPivot[y] + 245, 80, 20 * 2), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 110, LeftPivot[y] + 245, 80, 20 * 2), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(LeftPivot[x] - 20, LeftPivot[y] + 215, 20, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(LeftPivot[x] - 75, LeftPivot[y] + 215, 20, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//6UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(LeftPivot[x] - 50, LeftPivot[y] + 295, 168, 20), 0, b2BodyType::b2_dynamicBody);
	//7UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(LeftPivot[x] - 45, LeftPivot[y] + 325, 80, 20 * 2), 0 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//8UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(LeftPivot[x] - 45, LeftPivot[y] + 380, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);

	//Right 

	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(RightPivot[x], RightPivot[y], 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_staticBody);
	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(RightPivot[x] + 85, RightPivot[y], 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_staticBody);
	//1Up
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 70, RightPivot[y] + 40, 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 5, RightPivot[y] + 40, 20 * 2, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	//2Up
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 30, RightPivot[y] + 82, 168 * 0.5f, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 91, RightPivot[y] + 82, 20 * 2, 20 * 2), 0, b2BodyType::b2_dynamicBody);
	//3UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x], RightPivot[y] + 145, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 100, RightPivot[y] + 145, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::L1_LeftBlock, ImageName::StoneBlock_Healty, Rect(RightPivot[x] + 50, RightPivot[y] + 145, 80, 20 * 2), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//4Up
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 50, RightPivot[y] + 190, 168, 20), 0, b2BodyType::b2_dynamicBody);
	//5UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] - 20, RightPivot[y] + 245, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] - 0, RightPivot[y] + 245, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 120, RightPivot[y] + 245, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 100, RightPivot[y] + 245, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);

	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(RightPivot[x] + 25, RightPivot[y] + 215, 20, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(RightPivot[x] + 80, RightPivot[y] + 215, 20, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//6Up
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::LongWoodBlock_Healty, Rect(RightPivot[x] + 50, RightPivot[y] + 295, 168, 20), 0, b2BodyType::b2_dynamicBody);
	//7Up
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(RightPivot[x] + 45, RightPivot[y] + 325, 80, 20 * 2), 0 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//8UP
	BlockFactory::Create(GameObjectName::L1_LeftBlock, ImageName::GlassBlock_Healty, Rect(RightPivot[x] + 45, RightPivot[y] + 380, 80, 20), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);

	
	
}
void Level::Level_3PI_Test()
{
	Level * l = Level::privGetInstance();
	l->active = LevelName::LEVEL_3;
	
	GameObjectMan::CreateSorting();

	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300, 300, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280, 295, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 - 1280, 305, 1280, 1336));
	BackGroundFactory::Create(GameObjectName::L1_BackGround, ImageName::BackGround, Rect(300 + 1280 + 900, 295, 1280, 1336));

	Vect A(125.0f, 150.0f, 0.0f);
	SlingShotFactory::Create(A);
	Vect MainPivot(1500.0f, 80.0f, 0.0f);

	
	Vect ThreadMilPos(1050,500,0);
	Vect Pivot(ThreadMilPos[x]-100, 75.0f,0);
	ThreadMill::Create(GameObjectName::Block, ThreadMilPos,-3.0);
	ThreadMilPos.set(1050 + 300, 500, 0);
	ThreadMill::Create(GameObjectName::Block, ThreadMilPos, 3.0);


	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y], 80, 40), 0, b2BodyType::b2_staticBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y], 80, 40), 0, b2BodyType::b2_staticBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y]+40, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y]+40, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y]+80, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y]+80, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y] +120, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y] + 120, 80, 40), 0, b2BodyType::b2_dynamicBody);


	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x]-20, Pivot[y] + 160, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 40, Pivot[y] + 160, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80+20, Pivot[y] + 160, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] - 40, Pivot[y] + 200, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 20, Pivot[y] + 200, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 60, Pivot[y] + 200, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80 + 40, Pivot[y] + 200, 80, 40), 0, b2BodyType::b2_dynamicBody);


	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] -20, Pivot[y] + 260, 80, 40), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80 + 40, Pivot[y] + 260, 80, 40), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	//Right Side
	Pivot.set(Pivot[x] + 500, Pivot[y],0);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y], 80, 40), 0, b2BodyType::b2_staticBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y], 80, 40), 0, b2BodyType::b2_staticBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y] + 40, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y] + 40, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y] + 80, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y] + 80, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x], Pivot[y] + 120, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80, Pivot[y] + 120, 80, 40), 0, b2BodyType::b2_dynamicBody);


	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] - 20, Pivot[y] + 160, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 40, Pivot[y] + 160, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80 + 20, Pivot[y] + 160, 80, 40), 0, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] - 40, Pivot[y] + 200, 80, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 20, Pivot[y] + 200, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 60, Pivot[y] + 200, 40, 40), 0, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80 + 40, Pivot[y] + 200, 80, 40), 0, b2BodyType::b2_dynamicBody);


	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] - 20, Pivot[y] + 260, 80, 40), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);
	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x] + 80 + 40, Pivot[y] + 260, 80, 40), 90 * DEGTORAD, b2BodyType::b2_dynamicBody);

	StoneBlock::Create(GameObjectName::Block, ImageName::StoneBlock_Healty, Rect(Pivot[x]-200 , Pivot[y] +600, 150, 20), 0, b2BodyType::b2_staticBody);

	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 150, Pivot[y] + 630, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] -  180, Pivot[y] + 630, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 210 , Pivot[y] + 630, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 240 , Pivot[y] + 630, 30, 30), b2BodyType::b2_dynamicBody);
	
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 150, Pivot[y] + 660, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 180, Pivot[y] + 660, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 210, Pivot[y] + 660, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 240, Pivot[y] + 660, 30, 30), b2BodyType::b2_dynamicBody);

	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 150, Pivot[y] + 690, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 180, Pivot[y] + 690, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 210, Pivot[y] + 690, 30, 30), b2BodyType::b2_dynamicBody);
	StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(Pivot[x] - 240, Pivot[y] + 690, 30, 30), b2BodyType::b2_dynamicBody);

	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x]+50 , Pivot[y]+250, 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 450, Pivot[y] + 250, 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 300, Pivot[y] , 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 200, Pivot[y] , 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	PiggyFactory::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 100, Pivot[y] , 50.0f * Level::getScale(), 50.0f* Level::getScale()));


	HelmetPiggy::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 250, Pivot[y], 50.0f * Level::getScale(), 50.0f* Level::getScale()));
	HelmetPiggy::Create(GameObjectName::L1_Piggy, ImageName::Piggy_Healty, Rect(Pivot[x] - 150, Pivot[y], 50.0f * Level::getScale(), 50.0f* Level::getScale()));

	BlackBird::Create(GameObjectName::L1_RedBird, ImageName::BlackBird, Rect(A[X] + 250, A[Y] - 45, 60.0f * Level::getScale(), 80.0f* Level::getScale()));
	

	BlueBird::Create(GameObjectName::L1_RedBird, ImageName::BlueBird, Rect(A[X] - 100, A[Y] - 65, 32.0f * Level::getScale(), 30.0f* Level::getScale()));


	BlackBird::Create(GameObjectName::L1_RedBird, ImageName::BlackBird, Rect(A[X] - 250, A[Y] - 45, 60.0f * Level::getScale(), 80.0f* Level::getScale()));


	GreenBird::Create(GameObjectName::L1_RedBird, ImageName::GreenBird, Rect(A[X] - 180, A[Y] - 45, 100.0f * Level::getScale(), 75.0f* Level::getScale()));



	WhiteBird::Create(GameObjectName::L1_RedBird, ImageName::WhiteBird, Rect(A[X] + 350, A[Y] - 45, 85.0f * Level::getScale(), 95.0f* Level::getScale()));
	

	YellowBird::Create(GameObjectName::L1_RedBird, ImageName::YellowBird, Rect(A[X] + 170, A[Y] - 65, 58.0f * Level::getScale(), 54.0f* Level::getScale()));
	

	RedBird::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(A[X] + 20, A[Y] - 65, 45.0f * Level::getScale(), 45.0f* Level::getScale()));
	Bird *pBlue = RedBird::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(A[X] + 70, A[Y] - 65, 45.0f * Level::getScale(), 45.0f* Level::getScale()));
	GameObjectMan::setActiveBird(pBlue);
}

Level* Level::privGetInstance()
{
	static Level instance;
	return &instance;


}
float Level::getScale()
{
	Level * l = Level::privGetInstance();

	return l->scalefactor;

}
LevelName Level::getActive()
{
	Level * l = Level::privGetInstance();
	return l->active;
}
Level::Level() :scalefactor(1.0f)
{
	active = LevelName::LEVEL_1;
}

void Level::AddBird()
{
	Bird *pBird = (Bird*)GameObjectMan::Find(GameObjectName::Birds_Sort)->getChild();
	if (pBird == 0)
	{
		

		RubberBand* pBack = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandBack);
		RubberBand* pFront = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandFront);
		Vect A(pBack->anchorX, pBack->anchorY, 0);
		Vect B(pFront->anchorX, pFront->anchorY, 0);
		Vect C = B - A;
		float len = C.mag();
		C.norm();
		C = C* 0.5 * len;
		C = A + C;

		float scale = 1;
		if (Level::getActive() == LevelName::LEVEL_1)
			scale = 0.8f;

		BirdFactory::Create(GameObjectName::L1_RedBird, ImageName::RedBird, Rect(C[x], C[y], 50.0f * Level::getScale()*scale, 50.0f* Level::getScale()*scale));
	}


}