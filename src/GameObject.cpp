#include <assert.h>
#include <math.h>

#include "AzulHelper.h"
#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"

GameObject::GameObject( )
	: PCSNode()
{
	this->deleteMe = false;
	this->pWorld = new Matrix(MatrixSpecialType::IDENTITY);	
	assert(this->pWorld != 0);
}

GameObject::~GameObject()
{
	assert(this->deleteMe == true);
	delete this->pWorld;
}

Matrix &GameObject::getWorld()
{
	return *this->pWorld;
}

void GameObject::Update(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	this->WorldUpdate(currentTime);

	// push to graphics object
	if (this->getGraphicsObject())
	{
		this->getGraphicsObject()->SetWorld(*this->pWorld);
	}
}