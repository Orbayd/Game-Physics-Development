#ifndef GAME_OBJECT_NAME
#define GAME_OBJECT_NAME

#include "EnumBase.h"

struct GameObjectName : public EnumBase
{
	GameObjectName(GameObjectName::Name n)
	{
		this->value = n;
	}

	enum Name
	{
		Root = 0x70000,
		Orbay_Sort,
		Circle_Guideline,
		//SORTS
		BackGround_Sort,
		RubberBandFront_Sort,
		RubberBandBack_Sort,
		SlingShootSeat_Sort,
		SlingShootFront_Sort,
		SlingShootBack_Sort,
		Effects_Sort,
		Blocks_Sort,
		Birds_Sort,
		StaticObjects_Sort,
		SlingShootBack,
		SlingShootFront,
		SlingShootSeat,
		
		Level_PI_Sort,
		Block,
		GlassBlock,
		GlassTriangle,
		WoodenBlock,
		
		L1_BackGround,
		L1_RedBird,
		L1_Piggy,
		L1_RightBlock,
		L1_LeftBlock,	
		L1_BottomBlock,
		L1_TopBlock,

		L1_LeftUPBlock,
		L1_RightUPBlock,
		L1_UpBlock,
		L1_UpBottomBlock,

		L1_SmallLeftBlock,
		L1_SmallRightBlock,
		L1_SmallTopBlock,
		L1_SmallUpBlock,

		L1_MediumLeftBlock,
		L1_MediumRightBlock,
		L1_MediumBottomBlock,
		L1_MediumUpBlock,

		L2_RedBird,
		L2_LeftRightBlock,
		L2_LeftLeftBlock,
		L2_RightRightBlock,
		L2_RightLeftBlock,
		L2_TopRightBlock,
		L2_TopLeftBlock,
		L2_BottomBlock,
	
		RubberBandBack,
		RubberBandFront,
		Platform_1,
		Platform_2,
		Bang,
		Rubber,
		Ground,
		SlingShot_Sort,
		//New
		Smoke,
		SmokeBucket_A,
		SmokeBucket_A_Particle,
		SmokeBucket_B_Particle,
		SmokeBucket_B,
		Bomb_Particle,
		WoodChunk_Particle,
		SmokeParticle,
		NOT_INITIALIZED
	};
};

#endif