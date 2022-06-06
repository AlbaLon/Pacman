#include "ModuleRoundStart2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneRoundStart2::SceneRoundStart2(bool startEnabled) : Module(startEnabled)
{
	bgRstart2.PushBack({ 0, 0, 232, 304 });
	bgRstart2.PushBack({ 233, 0, 232, 304 });
	bgRstart2.PushBack({ 465, 0, 232, 304 });
	bgRstart2.PushBack({ 697, 0, 232, 304 });
	bgRstart2.PushBack({ 929, 0, 232, 304 });
	bgRstart2.PushBack({ 1161, 0, 232, 304 });
	bgRstart2.PushBack({ 1393, 0, 232, 304 });
	bgRstart2.PushBack({ 1625, 0, 232, 304 });
	bgRstart2.PushBack({ 1857, 0, 232, 304 });
	bgRstart2.PushBack({ 2089, 0, 232, 304 });
	bgRstart2.PushBack({ 2321, 0, 232, 304 });
	bgRstart2.PushBack({ 0, 305, 232, 304 });
	bgRstart2.PushBack({ 233, 305, 232, 304 });
	bgRstart2.PushBack({ 465, 305, 232, 304 });
	bgRstart2.PushBack({ 697, 305, 232, 304 });
	bgRstart2.PushBack({ 929, 305, 232, 304 });
	bgRstart2.PushBack({ 1161, 305, 232, 304 });
	bgRstart2.PushBack({ 1393, 305, 232, 304 });
	bgRstart2.PushBack({ 1625, 305, 232, 304 });
	bgRstart2.PushBack({ 1857, 305, 232, 304 });
	bgRstart2.PushBack({ 2089, 305, 232, 304 });
	bgRstart2.PushBack({ 2321, 305, 232, 304 });
	bgRstart2.loop = false;
	bgRstart2.pingpong = false;
	bgRstart2.speed = 0.2f;
}

SceneRoundStart2::~SceneRoundStart2()
{

}

// Load assets
bool SceneRoundStart2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Round 2 Animado.png");
	App->audio->PlayMusic("Assets/Fx/round_start.wav", 1.0f);

	Rstart2Anim = &bgRstart2;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//App->collisions->CleanUp();
	return ret;
}



Update_Status SceneRoundStart2::Update()
{
	Rstart2Anim->Update();

	//if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { //TODO: ELIMINAR ESTO

	//}
	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	//{
	//	App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 90);
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRoundStart2::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rectRstart = Rstart2Anim->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectRstart);


	return Update_Status::UPDATE_CONTINUE;
}
