#include "ModuleRoundClear.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneRoundClear::SceneRoundClear(bool startEnabled) : Module(startEnabled)
{
	bgRClear.PushBack({ 0, 0, 232, 304 });
	bgRClear.PushBack({ 233, 0, 232, 304 });
	bgRClear.PushBack({ 465, 0, 232, 304 });
	bgRClear.PushBack({ 697, 0, 232, 304 });
	bgRClear.PushBack({ 929, 0, 232, 304 });
	bgRClear.PushBack({ 1161, 0, 232, 304 });
	bgRClear.PushBack({ 1393, 0, 232, 304 });
	bgRClear.PushBack({ 1625, 0, 232, 304 });
	bgRClear.PushBack({ 1857, 0, 232, 304 });
	bgRClear.PushBack({ 2089, 0, 232, 304 });
	bgRClear.PushBack({ 2321, 0, 232, 304 });
	bgRClear.PushBack({ 0, 305, 232, 304 });
	bgRClear.PushBack({ 233, 305, 232, 304 });
	bgRClear.PushBack({ 465, 305, 232, 304 });
	bgRClear.PushBack({ 697, 305, 232, 304 });
	bgRClear.PushBack({ 929, 305, 232, 304 });
	bgRClear.PushBack({ 1161, 305, 232, 304 });
	bgRClear.PushBack({ 1393, 305, 232, 304 });
	bgRClear.PushBack({ 1625, 305, 232, 304 });
	bgRClear.PushBack({ 1857, 305, 232, 304 });
	bgRClear.PushBack({ 2089, 305, 232, 304 });
	bgRClear.PushBack({ 2321, 305, 232, 304 });
	bgRClear.loop = false;
	bgRClear.pingpong = false;
	bgRClear.speed = 0.1f;
}

SceneRoundClear::~SceneRoundClear()
{

}

// Load assets
bool SceneRoundClear::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Round Clear Animated.png");
	App->audio->PlayMusic("Assets/Fx/intro.wav", 1.0f);

	RClearAnim = &bgRClear;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//App->collisions->CleanUp();
	return ret;
}



Update_Status SceneRoundClear::Update()
{
	RClearAnim->Update();

	//FALTA HACER QUE SE INICIE ESTA ESCENA AL TERMINAR UNA RONDA

	//if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { //TODO: ELIMINAR ESTO

	//}
	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	//{
	//	App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 90);
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRoundClear::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rectRC = RClearAnim->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectRC);


	return Update_Status::UPDATE_CONTINUE;
}
