#ifndef BIRD_ABILITIES_H
#define BIRD_ABILITIES_H
class Bird;
class Ability
{
public:
	virtual  void Execute(Bird * pBird) =0;
private:

};

class NoAbility : public  Ability
{
public:
	void Execute(Bird * pBird)override{ pBird; };
	static NoAbility *getInstance()
	{
		static NoAbility instance;
		return & instance;
	}
private:

};




#endif