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
	int musicafinalFx = App->audio->LoadFx("Assets/Fx/round_start.wav");
	App->audio->PlayFx(musicafinalFx, 0);
	App->audio->PlayMusic("Assets/Music/final_boss_fase1.ogg", 1.0f);



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
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 6 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 40);
		if (multiplier == 10) { multiplier = 18; }
		++App->particles->COUNTDOWN;
	};
	for (int altura = 6; altura <= 31; ++altura) // Repeticion de . .       . .
	{
		if (altura == 9) { altura = 10; }
		if (altura == 16) { altura = 20; }
		if (altura == 22) { altura = 25; }
		if (altura == 25) { altura = 29; }

		for (multiplier = 4; multiplier <= 25; ++multiplier)
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, altura * 8);
			if (multiplier == 4) { multiplier = 9; }
			if (multiplier == 10) { multiplier = 18; }
			if (multiplier == 19) { multiplier = 24; }

			++App->particles->COUNTDOWN;

		};
	}
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 9
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 72);

		++App->particles->COUNTDOWN;
	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 6 P1
	{
		if (multiplier == 8) { multiplier = 10; }
		if (multiplier == 11) { multiplier = 19; }
		if (multiplier == 20) { multiplier = 22; }
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 128);

		++App->particles->COUNTDOWN;
	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 10 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 136);
		if (multiplier == 4) { App->particles->AddParticle(App->particles->powerpellet, 8 * multiplier + 24, 136); }
		if (multiplier == 4) { multiplier = 9; }
		if (multiplier == 22) { App->particles->AddParticle(App->particles->powerpellet, 8 * multiplier - 24, 136); }
		if (multiplier == 10) { multiplier = 21; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 11 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 144);
		if (multiplier == 4) { multiplier = 6; }
		if (multiplier == 7) { multiplier = 9; }
		if (multiplier == 10) { multiplier = 18; }
		if (multiplier == 19) { multiplier = 21; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 12 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 152);
		if (multiplier == 4) { multiplier = 6; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 15 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 184);
		if (multiplier == 4) { multiplier = 12; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 16) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 16 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 192);
		if (multiplier == 4) { multiplier = 12; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 16) { multiplier = 24; }

		++App->particles->COUNTDOWN;
	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 12 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 200);
		if (multiplier == 4) { multiplier = 6; }
		if (multiplier == 10) { multiplier = 12; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 16) { multiplier = 18; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 12 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 208);
		if (multiplier == 4) { multiplier = 6; }
		if (multiplier == 7) { multiplier = 12; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 16) { multiplier = 21; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 12 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 216);
		if (multiplier == 4) { multiplier = 6; }
		if (multiplier == 7) { multiplier = 12; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 16) { multiplier = 21; }
		if (multiplier == 22) { multiplier = 24; }

		++App->particles->COUNTDOWN;

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 12 P1
	{

		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 224);
		if (multiplier == 5) { multiplier = 6; }
		if (multiplier == 7) { multiplier = 9; }
		if (multiplier == 13) { multiplier = 15; }
		if (multiplier == 18) { multiplier = 21; }
		if (multiplier == 22) { App->particles->AddParticle(App->particles->powerpellet, 8 * multiplier + 8, 224); }
		if (multiplier == 22) { multiplier = 23; }

		++App->particles->COUNTDOWN;
		if (multiplier == 6) { App->particles->AddParticle(App->particles->powerpellet, 8 * multiplier, 224); }

	};
	for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 32 P1
	{
		App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 256);
		if (multiplier == 10) { multiplier = 18; }
		++App->particles->COUNTDOWN;
	};



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
	}
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 30);
	}
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 30);
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->win, 30);
	}
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->gameover, 30);
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
	return true;
}
