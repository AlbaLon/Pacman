#include "ModuleRoundStart1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneRoundStart1::SceneRoundStart1(bool startEnabled) : Module(startEnabled)
{
	bgRstart1.PushBack({ 0, 0, 232, 304 });
	bgRstart1.PushBack({ 233, 0, 232, 304 });
	bgRstart1.PushBack({ 465, 0, 232, 304 });
	bgRstart1.PushBack({ 697, 0, 232, 304 });
	bgRstart1.PushBack({ 929, 0, 232, 304 });
	bgRstart1.PushBack({ 1161, 0, 232, 304 });
	bgRstart1.PushBack({ 1393, 0, 232, 304 });
	bgRstart1.PushBack({ 1625, 0, 232, 304 });
	bgRstart1.PushBack({ 1857, 0, 232, 304 });
	bgRstart1.PushBack({ 2089, 0, 232, 304 });
	bgRstart1.PushBack({ 2321, 0, 232, 304 });
	bgRstart1.PushBack({ 0, 305, 232, 304 });
	bgRstart1.PushBack({ 233, 305, 232, 304 });
	bgRstart1.PushBack({ 465, 305, 232, 304 });
	bgRstart1.PushBack({ 697, 305, 232, 304 });
	bgRstart1.PushBack({ 929, 305, 232, 304 });
	bgRstart1.PushBack({ 1161, 305, 232, 304 });
	bgRstart1.PushBack({ 1393, 305, 232, 304 });
	bgRstart1.PushBack({ 1625, 305, 232, 304 });
	bgRstart1.PushBack({ 1857, 305, 232, 304 });
	bgRstart1.PushBack({ 2089, 305, 232, 304 });
	bgRstart1.PushBack({ 2321, 305, 232, 304 });
	bgRstart1.loop = false;
	bgRstart1.pingpong = false;
	bgRstart1.speed = 0.2f;
}

SceneRoundStart1::~SceneRoundStart1()
{

}

// Load assets
bool SceneRoundStart1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Round 1 Animado.png");
	App->audio->PlayMusic("Assets/Fx/Inicio_de_partida.wav", 1.0f);

	Rstart1Anim = &bgRstart1;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//App->collisions->CleanUp();
	return ret;
}



Update_Status SceneRoundStart1::Update()
{
	Rstart1Anim->Update();

	//if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { //TODO: ELIMINAR ESTO

	//}
	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	//{
	//	App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 90);
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRoundStart1::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rectRstart = Rstart1Anim->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectRstart);


	return Update_Status::UPDATE_CONTINUE;
}
