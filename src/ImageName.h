#ifndef IMAGE_NAME
#define IMAGE_NAME


#include "EnumBase.h"

struct ImageName : public EnumBase
{
	ImageName(ImageName::Name n)
	{
		this->value = n;
	}

	enum Name
	{
		LongWoodBlock_Healty = 0x30000,
		LongWoodBlock_Minor,
		LongWoodBlock_Moderate,
		LongWoodBlock_NearDead,

		GlassBlock_Healty,
		GlassBlock_Minor,
		GlassBlock_Moderate,
		GlassBlock_NearDead,

		StoneBlock_Healty,
		StoneBlock_Minor,
		StoneBlock_Moderate,
		StoneBlock_NearDead,
		
		StoneBall_Healty,

		Piggy_Healty,
		Piggy_HealtyBlink,
		Piggy_HealtySmile,
		
		Piggy_Dmged,
		Piggy_DmgedBlink,
		Piggy_DmgedSmile,

		Piggy_HeavyDmged,
		Piggy_HeavyDmgedBlink,
		Piggy_HeavyDmgedSmile,

		RubberBand,

		XLWoodBlock,
		MediumWoodBlock,
		SmallWoodBlock,

		RedBird,
		RedBirdBlink,
		RedBirdSmile,
		RedBirdDamaged,

		BlackBird,
		BlackBirdBlink,
		BlackBirdSmile,
		BlackBirdFly,
		BlackBirdBombPhase_1,
		BlackBirdBombPhase_2,
		BlackBirdBombPhase_3,

		YellowBird,
		YellowBirdBlink,
		YellowBirdSmile,
		YellowBirdFly,
		YellowBirdAbility,
		YellowBirdDamaged,
		
		BlueBird,
		BlueBirdBlink,
		BlueBirdSmile,
		BlueBirdDamaged,

		WhiteBird,
		WhiteBirdBlink,
		WhiteBirdSmile,
		WhiteBirdAbility,
		WhiteBirdUdk,
		WhiteBirdDamaged,

		GreenBird,
		GreenBirdBlink,
		GreenBirdSmile,
		GreenBirdAbility,
		GreenBirdDamaged,

		Bang,
		Egg,
		GlassBlock,
		GlassTriangle,
		WoodPlatform,
		SlingshotFront,
		SlingshotBack,
		Not_Initialized,

		WoodChunk_0,
		WoodChunk_1,
		WoodChunk_2,
		StoneChunk_0,
		StoneChunk_1,
		StoneChunk_2,
		GlassChunk_0,
		GlassChunk_1,
		GlassChunk_2,

		RedFeather,
		OrangeFeather,
		BrownFeather,
		Smoke,
		SmokeExplosion_0,
		SmokeExplosion_1,
		SmokeExplosion_2,
		SmokeExplosion_3,
		SmokeExplosion_4,

		SmallSmoke,
		SmallSmoke1,
		SmallSmoke2,
		SmallSmoke3,
		Sky,
		Helmet,
		BackGround
	};
};

#endif