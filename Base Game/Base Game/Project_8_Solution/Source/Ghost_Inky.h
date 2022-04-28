#pragma once
//TODO (HAY EJEMPLOS DE LOS OTROS ENEMYS)

#ifndef __ENEMY_INKY_H__
#define __ENEMY_INKY_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Inky : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Inky(int x, int y);

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

#endif 