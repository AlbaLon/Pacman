#ifndef __MODULE_PACDOT_H__
#define __MODULE_PACDOT_H__

#include "Module.h"
#include "Animation.h"

#define MAX_PACDOTS 100

//ESCENAS/NIVELES
#include "SceneLevel1.h"

struct SDL_Texture;
struct Collider;

class ModulePacDot : public Module
{
public:
	// Constructor
	ModulePacDot(bool startEnabled);

	// Destructor
	~ModulePacDot();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	fPoint position;

	// Position of packman in the TileSet ERIC

	iPoint tile;
	//ERIC: INTENTO DE DEFINIR LAS POSICIONES QUE TIENE EN SUS EJES

	//MAX I POSITION=29 (0-28))
	//MAX I POSITION=38 (0-37))
	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations TODO: Ampliar
	Animation idleAnim; //Animación de inicio, luego no vuelve a usarse

	Animation deathAnim; //Animacion de muerte

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// God mode
	bool inmortality = false;

};

#endif //!__MODULE_PACDOT_H__
