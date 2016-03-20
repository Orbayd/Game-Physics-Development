#include <assert.h>
#include "InputMan.h"


InputMan *InputMan::pInputMan = 0;

void InputMan::Create( )
{
	InputMan::privCreate( );
}

InputMan::InputMan( )
{
	this->pKeyboard = new Keyboard(  );
	assert(this->pKeyboard);
}

void InputMan::privCreate(   )
{
	InputMan::pInputMan = new InputMan(  );
}

InputMan::~InputMan()
{
	delete this->pKeyboard;
}

Keyboard *InputMan::GetKeyboard()
{
	InputMan *pInputMan = InputMan::privInstance();
	return pInputMan->pKeyboard;
}


Mouse *InputMan::GetMouse()
{
	InputMan *pInputMan = InputMan::privInstance();
	return pInputMan->pMouse;
}

InputMan *InputMan::privInstance()
{
	assert( pInputMan );
	return pInputMan;
}

