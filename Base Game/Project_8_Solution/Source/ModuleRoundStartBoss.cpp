#include "ModuleRoundStartBoss.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneRoundStartBoss::SceneRoundStartBoss(bool startEnabled) : Module(startEnabled)
{
	bgRstartB.PushBack({ 0, 0, 232, 304 });
	bgRstartB.PushBack({ 233, 0, 232, 304 });
	bgRstartB.PushBack({ 465, 0, 232, 304 });
	bgRstartB.PushBack({ 697, 0, 232, 304 });
	bgRstartB.PushBack({ 929, 0, 232, 304 });
	bgRstartB.PushBack({ 1161, 0, 232, 304 });
	bgRstartB.PushBack({ 1393, 0, 232, 304 });
	bgRstartB.PushBack({ 1625, 0, 232, 304 });
	bgRstartB.PushBack({ 1857, 0, 232, 304 });
	bgRstartB.PushBack({ 2089, 0, 232, 304 });
	bgRstartB.PushBack({ 2321, 0, 232, 304 });
	bgRstartB.PushBack({ 0, 305, 232, 304 });
	bgRstartB.PushBack({ 233, 305, 232, 304 });
	bgRstartB.PushBack({ 465, 305, 232, 304 });
	bgRstartB.PushBack({ 697, 305, 232, 304 });
	bgRstartB.PushBack({ 929, 305, 232, 304 });
	bgRstartB.PushBack({ 1161, 305, 232, 304 });
	bgRstartB.PushBack({ 1393, 305, 232, 304 });
	bgRstartB.PushBack({ 1625, 305, 232, 304 });
	bgRstartB.PushBack({ 1857, 305, 232, 304 });
	bgRstartB.PushBack({ 2089, 305, 232, 304 });
	bgRstartB.PushBack({ 2321, 305, 232, 304 });
	bgRstartB.loop = false;
	bgRstartB.pingpong = false;
	bgRstartB.speed = 0.2f;
}

SceneRoundStartBoss::~SceneRoundStartBoss()
{

}

// Load assets
bool SceneRoundStartBoss::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Boss Round Animado.png");
	App->audio->PlayMusic("Assets/Fx/round_start.wav", 1.0f);

	RstartBAnim = &bgRstartB;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//App->collisions->CleanUp();
	return ret;
}



Update_Status SceneRoundStartBoss::Update()
{
	RstartBAnim->Update();

	//if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { //TODO: ELIMINAR ESTO

	//}
	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	//{
	//	App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 90);
	//}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneRoundStartBoss::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rectRstart = RstartBAnim->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectRstart);


	return Update_Status::UPDATE_CONTINUE;
}
