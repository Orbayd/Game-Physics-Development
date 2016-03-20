#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "GameObjectName.h"

class GameObject : public PCSNode
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void WorldUpdate(float t) = 0;
	virtual EnumBase getName() = 0;
	virtual bool HasBody() = 0;
	void Update(float t);
	Matrix &getWorld();

	virtual GraphicsObject *getGraphicsObject() = 0;
	virtual bool drawEnabled() = 0;

	bool deleteMe;
protected:
	Matrix	*pWorld;
	

private:
	// prevent from calling
	GameObject( GameObject &copy);

};


#endif