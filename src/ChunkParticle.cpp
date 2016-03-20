#include <assert.h>

#include "ChunkParticle.h"
#include "PixelToMeter.h"
#include "World.h"

#include "GameObjectMan.h"
#include "AzulHelper.h"
#include "Simulation.h"
ChunkParticle::ChunkParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:FeatherParticle(name, pSprite, pSort)
{

}

ChunkParticle *ChunkParticle::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	ChunkParticle *pParticle = new ChunkParticle(gObjName, pSprite, pSort);
	assert(pParticle);

	return pParticle;
}

