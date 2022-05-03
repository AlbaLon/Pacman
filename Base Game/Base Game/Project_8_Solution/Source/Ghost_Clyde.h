#ifndef __ENEMY_CLYDE_H__
#define __ENEMY_CLYDE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Clyde : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Clyde(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation up; //TODO
	Animation down;
	Animation rigth;
	Animation left;
};

#endif // __ENEMY_CLYDE_H__
#pragma once
