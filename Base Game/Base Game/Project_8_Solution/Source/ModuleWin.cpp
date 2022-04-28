#include "ModuleWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	
	bgTexture = App->textures->Load("Assets/Sprites/win.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}



Update_Status SceneWin::Update()
{
	App->render->camera.x += 15;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}
