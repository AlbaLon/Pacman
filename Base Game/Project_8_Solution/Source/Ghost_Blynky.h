#ifndef __ENEMY_BLYNKY_H__
#define __ENEMY_BLYNKY_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Blinky : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Blinky(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//GHOST DIRECTIONS

	enum DIRECTIONS
	{
		UP,
		LEFT,
		DOWN,
		RIGTH,
	};

	int currentDirection;
	int newDir;

	//GHOST MODES
	enum MODES
	{
		CHASE,
		SCATTER,
		FEAR,
		EATEN,
	};

	int currentMode;

	//Movement speed
	float Movementspeed=0.8f;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation up; //TODO
	Animation down;
	Animation rigth;
	Animation left;
};

#endif // __ENEMY_MECH_H__
