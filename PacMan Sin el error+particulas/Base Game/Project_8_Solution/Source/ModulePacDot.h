
#ifndef __MODULE_PACDOT_H__
#define __MODULE_PACDOT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Enemy.h"
#include "Path.h"

#define MAX_PACDOTS 100

//ESCENAS/NIVELES
#include "SceneLevel1.h"



struct Collider;

struct Pacdot
{
public:
	// Constructor
	ModulePacDot();

	// Copy constructor
	ModulePacDot(const Particle& p);

	// Destructor
	~ModulePacDot();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();

public:
	// Defines the position in the screen
	iPoint position;


	// A set of rectangle sprites
	Animation idleAnim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	// The particle's collider
	Collider* collider = nullptr;
};

#endif //!__MODULE_PACDOT_H__




//ANIMACION PARTICULA

////idleAnim.PushBack({ 0, 0, 7, 22 });
//idleAnim.PushBack({ 8, 0, 7, 22 });
//idleAnim.PushBack({ 15, 0, 7, 22 });
//idleAnim.PushBack({ 23, 0, 7, 22 });
//idleAnim.PushBack({ 41, 0, 7, 22 });
//idleAnim.PushBack({ 49, 0, 7, 22 });
//idleAnim.PushBack({ 57, 0, 7, 22 });
//idleAnim.PushBack({ 65, 0, 7, 22 });
//idleAnim.loop = true;
//idleAnim.speed = 0.2f;
//
//currentAnimation = &idleAnim;