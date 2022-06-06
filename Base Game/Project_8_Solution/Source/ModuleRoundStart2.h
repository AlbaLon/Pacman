#ifndef __SCENE_ROUNDSTART2_H__
#define __SCENE_ROUNDSTART2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneRoundStart2 : public Module
{
public:
	//Constructor
	SceneRoundStart2(bool startEnabled);

	//Destructor
	~SceneRoundStart2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture

	SDL_Texture* bgTexture = nullptr;
	Animation bgRstart2;
	Animation* Rstart2Anim;
};

#endif

