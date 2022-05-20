#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

public:
	// The current position in the world
	fPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr; //DUDA: Quiza hay que poner lo del fantasma y no texture porque es null pointer

	// Sound fx when destroyed
	int destroyedFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	fPoint spawnPos;
	
	//Tile Movement
	iPoint tile;
	iPoint tileUp;
	iPoint tileDown;
	iPoint tileLeft;
	iPoint tileRight;

	//Where the ghost tries to go
	fPoint objectives;

	int timer = 0;
};

#endif // __ENEMY_H__