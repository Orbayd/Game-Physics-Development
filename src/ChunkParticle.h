#ifndef CHUNK_PARTICLE_H
#define CHUNK_PARTICLE_H

#include "FeatherParticle.h"

class ChunkParticle : public FeatherParticle
{
public:
	// Create
	ChunkParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	ChunkParticle() = delete;
	virtual ~ChunkParticle(){}

	static ChunkParticle *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	//virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) ;
	//virtual void WorldUpdate(float currentTime) ;
private:

};


#endif