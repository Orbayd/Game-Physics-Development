#ifndef SLINGSHOT_FACTORY_H
#define  SLINGSHOT_FACTORY
#include "GameObject2D.h"
class SlingShotFactory
{
public:

	static void Create(Vect &pivot);
	
private:
	static void CreateRubberBand(Vect &pivot);
	static void CreateBody(GameObject2D  *  pBlock);
	static void CreateSeat(Vect &pivot);
};




#endif
