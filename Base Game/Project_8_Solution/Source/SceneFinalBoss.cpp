#include "SceneFinalBoss.h"

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

SceneFinalBoss::SceneFinalBoss(bool startEnabled) : Module(startEnabled)
{

}

SceneFinalBoss::~SceneFinalBoss()
{

}

// Load assets
bool SceneFinalBoss::Start()
{
	int scene = 2;

	LOG("Loading background assets");

	bool ret = true;

	//bgTexture = App->textures->Load("Assets/Sprites/map.png"); //ERIC: CAMBIADO AL MAPA
	bgTexture = App->textures->Load("Assets/Sprites/finalbossmap.png"); //La grid para ver movimiento pac man  
	int musicainicioFx = App->audio->LoadFx("Assets/Fx/Inicio_de_partida.wav");
	App->audio->PlayFx(musicainicioFx, 0);
	App->audio->PlayMusic("Assets/Music/musica_mundo_1.ogg", 1.0f);



	//PRINT COLIDERS PAREDES
	for (int j = 0; j <= 28; ++j)
	{
		for (int i = 0; i <= 37; ++i)
		{
			LOG("En %d,%d hay un %d", i, j, TileSet[i][j])
		}
	}




	// Enemies ---


	//Place all the Pac-Dots in the scene.
	int multiplier;
	int altura;
	App->particles->COUNTDOWN = 0;
	for (int altura = 8; altura <= 32; ++altura) // Repeticion de . .       . .
	{
		
		if (altura == 9) { altura = 11; }
		if (altura == 12) { altura = 15; }
		if (altura == 16) { altura = 19; }
		if (altura == 20) { altura = 22; }
		if (altura == 23) { altura = 26; }
		if (altura == 27) { altura = 29; }
		if (altura == 30) { altura = 32; }

		for (multiplier = 2; multiplier <= 26; ++multiplier)
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, altura * 8);
			

			++App->particles->COUNTDOWN;

		};
	}
	for (int altura = 10; altura <= 30; ++altura) // Repeticion de . .       . .
	{

		if (altura == 11) { altura = 13; }
		if (altura == 15) { altura = 17; }
		if (altura == 18) { altura = 21; }
		if (altura == 22) { altura = 24; }
		if (altura == 25) { altura = 28; }
		if (altura == 29) { altura = 31; }
		

		for (multiplier = 2; multiplier <= 26; ++multiplier)
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, altura * 8);
			if (multiplier == 3) { multiplier = 4; } //GOOD
			if (multiplier == 6) { multiplier = 8; }
			if (multiplier == 10) { multiplier = 12; }
			if (multiplier == 14) { multiplier = 15; }
			if (multiplier == 17) { multiplier = 19; }
			if (multiplier == 21) { multiplier = 23; }
			++App->particles->COUNTDOWN;

		};
	}
	



	App->enemies->AddEnemy(Enemy_Type::BLINKY, 112, 136); //ERIC: Hay un bug cuando solo hay un fantasma
	//App->enemies->AddEnemy(Enemy_Type::BLINKY, 16, 216);
	//App->enemies->AddEnemy(Enemy_Type::PINKY, 120, 136);
	App->enemies->AddEnemy(Enemy_Type::INKY, 104, 136);
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 104, 128);
	App->enemies->AddEnemy(Enemy_Type::KINKY, 104, 120);


	/*App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);*/



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();

	return ret;
}

Update_Status SceneFinalBoss::Update()
{
	/*App->render->camera.x += 15;*/

	if (App->particles->COUNTDOWN <= 0)
	{
		LOG("VICTORY");
		App->fade->FadeToBlack(this, (Module*)App->win, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg");

	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->win, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
	}
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->gameover, 30);
		App->audio->PlayMusic("Assets/Music/Ending.ogg");
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneFinalBoss::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneFinalBoss::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// ERIC: ELIMINAR COSAS AL REEMPEZAR
	App->player->CleanUp();
	App->enemies->CleanUp();
	App->particles->CleanUp();
	App->collisions->Destroy(App->player->collider);
	App->audio->CleanUp();
	return true;
}
