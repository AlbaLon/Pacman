#include "SceneLevel1.h"

#include "ModuleInput.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	//bgTexture = App->textures->Load("Assets/Sprites/map.png"); //ERIC: CAMBIADO AL MAPA
	bgTexture = App->textures->Load("Assets/Sprites/grid.png"); //La grid para ver movimiento pac man  
	int musicainicioFx = App->audio->LoadFx("Assets/Fx/Inicio_de_partida.wav");
	App->audio->PlayFx(musicainicioFx, 0);
	App->audio->PlayMusic("Assets/Music/musica_mundo_1.ogg", 1.0f);




	// Enemies ---
	//TODO: PONER A LOS DOS FANTASMAS EN SU SITIO 
	int multiplier;
	
		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 6 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 32);
			if (multiplier == 13) { multiplier = 15; }

		};
		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila  P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 232);
			if (multiplier == 13) { multiplier = 15; }

		}; for (multiplier = 5; multiplier <= 24; ++multiplier) //Fila 6 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 184);
			if (multiplier == 13) { multiplier = 15; }

		};
	
	

		for (multiplier = 6; multiplier <= 10; ++multiplier) //Fila 8 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 56);

		};
	
	
	

	/*App->enemies->AddEnemy(Enemy_Type::REDBIRD, 32, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 665, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);*/

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 15;

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->win, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg", 1.0f);
	}
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->gameover, 30);
		App->audio->PlayMusic("Assets/Music/Ending.ogg");
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}