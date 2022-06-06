#include "ModuleGameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneGameOver::SceneGameOver(bool startEnabled) : Module(startEnabled)
{
	bgGOver.PushBack({ 0, 0, 232, 304 });
	bgGOver.PushBack({ 233, 0, 232, 304 });
	bgGOver.PushBack({ 465, 0, 232, 304 });
	bgGOver.PushBack({ 697, 0, 232, 304 });
	bgGOver.PushBack({ 929, 0, 232, 304 });
	bgGOver.PushBack({ 1161, 0, 232, 304 });
	bgGOver.PushBack({ 1393, 0, 232, 304 });
	bgGOver.PushBack({ 1625, 0, 232, 304 });
	bgGOver.PushBack({ 1857, 0, 232, 304 });
	bgGOver.PushBack({ 2088, 0, 232, 304 });
	bgGOver.PushBack({ 0, 305, 232, 304 });
	bgGOver.PushBack({ 233, 305, 232, 304 });
	bgGOver.PushBack({ 465, 305, 232, 304 });
	bgGOver.PushBack({ 697, 305, 232, 304 });
	bgGOver.PushBack({ 929, 305, 232, 304 });
	bgGOver.PushBack({ 1161, 305, 232, 304 });
	bgGOver.PushBack({ 1393, 305, 232, 304 });
	bgGOver.PushBack({ 1625, 305, 232, 304 });
	bgGOver.PushBack({ 1857, 305, 232, 304 });
	bgGOver.PushBack({ 2088, 305, 232, 304 });
	bgGOver.loop = false;
	bgGOver.pingpong = false;
	bgGOver.speed = 0.2f;
}

SceneGameOver::~SceneGameOver()
{

}

// Load assets
bool SceneGameOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Game Over Animated.png");
	App->audio->PlayMusic("Assets/Music/gameover.ogg", 1.0f);

	GameOverAnim = &bgGOver;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//App->collisions->CleanUp();
	return ret;
}



Update_Status SceneGameOver::Update()
{

	

	GameOverAnim->Update();


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect rectGOver = GameOverAnim->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectGOver);

	return Update_Status::UPDATE_CONTINUE;
}
