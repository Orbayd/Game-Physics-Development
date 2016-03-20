#ifndef LEVEL_H
#define LEVEL_H

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

enum LevelName
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	NOT_INITIALIZED,
};

class Level
{
public:
	static void Level_PI();
	static void Level_2PI();
	static void Level_PI_Test();
	static void Level_2PI_Test();
	static void Level_3PI_Test();
	static float getScale();
	static LevelName getActive();
	static void AddBird();
private:
	Level();
	static Level *privGetInstance();
	float scalefactor;
	LevelName active;
};

#endif