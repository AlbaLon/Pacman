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

	bgTexture = App->textures->Load("Assets/Sprites/map.png"); //ERIC: CAMBIADO AL MAPA
	//bgTexture = App->textures->Load("Assets/Sprites/grid.png"); //La grid para ver movimiento pac man  
	int musicainicioFx = App->audio->LoadFx("Assets/Fx/Inicio_de_partida.wav");
	App->audio->PlayFx(musicainicioFx, 0);
	App->audio->PlayMusic("Assets/Music/musica_mundo_1.ogg", 1.0f);




	// Enemies ---
	//TODO: PONER A LOS DOS FANTASMAS EN SU SITIO 
	int multiplier;
	int altura;
	App->particles->COUNTDOWN = 0;
		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 6 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 40);
			if (multiplier == 12) { multiplier = 14; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 7 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 48);
			if (multiplier == 4) { multiplier = 11; }
			if (multiplier == 12) { multiplier = 14; }
			if (multiplier == 15) { multiplier = 24; }
			++App->particles->COUNTDOWN;

		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 8 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 56);
			if (multiplier == 4) { multiplier = 11; }
			if (multiplier == 15) { multiplier = 24; }
			++App->particles->COUNTDOWN;

		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 9 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 64);
			if (multiplier == 2) { multiplier = 6; }
			if (multiplier == 10) { multiplier = 18; }
			if (multiplier == 22) { multiplier = 26; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 10 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 72);
			if (multiplier == 2) { multiplier = 6; }
			if (multiplier == 7) { multiplier = 9; }
			if (multiplier == 10) { multiplier = 18; }
			if (multiplier == 19) { multiplier = 21; }
			if (multiplier == 22) { multiplier = 26; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 11 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 80);
			if (multiplier == 7) { multiplier = 9; }
			if (multiplier == 10) { multiplier = 18; }
			if (multiplier == 19) { multiplier = 21; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 10; multiplier <= 19; ++multiplier) //Fila 12 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 88);
			
			if (multiplier == 10) { multiplier = 18; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 10; multiplier <= 19; ++multiplier) //Fila 13 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 96);

			if (multiplier == 10) { multiplier = 18; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 4; multiplier <= 24; ++multiplier) //Fila 14 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 104);
			if (multiplier == 10) { multiplier = 18; }
			++App->particles->COUNTDOWN;
		}
	for (int altura = 14; altura <= 23; ++altura)//Fila 15-24 P1
	{

		for (multiplier = 4; multiplier <= 24; ++multiplier)
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 8 * altura);
			if (multiplier == 4) { multiplier = 23; }
			++App->particles->COUNTDOWN;
		};
	}
		for (multiplier = 5; multiplier <= 24; ++multiplier) //Fila 25 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 184);
			if (multiplier == 12) { multiplier = 14; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 12; multiplier <= 15; ++multiplier) //Fila 26 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 192);
			if (multiplier == 12) { multiplier = 14; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 12; multiplier <= 15; ++multiplier) //Fila 27 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 200);
			if (multiplier == 12) { multiplier = 14; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 28 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 208);
			if (multiplier == 7) { multiplier = 9; }
			if (multiplier == 11) { multiplier = 15; }
			if (multiplier == 19) { multiplier = 20; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 29 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 216);
			if (multiplier == 2) { multiplier = 6; }
			if (multiplier == 7) { multiplier = 9; }
			if (multiplier == 10) { multiplier = 11; }
			if (multiplier == 12) { multiplier = 14; }
			if (multiplier == 15) { multiplier = 18; }
			if (multiplier == 19) { multiplier = 21; }
			if (multiplier == 22) { multiplier = 26; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 30 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 224);
			if (multiplier == 2) { multiplier = 6; }
			if (multiplier == 10) { multiplier = 11; }
			if (multiplier == 12) { multiplier = 14; }
			if (multiplier == 15) { multiplier = 18; }
			if (multiplier == 22) { multiplier = 26; }
			++App->particles->COUNTDOWN;
		};
		for (multiplier = 2; multiplier <= 27; ++multiplier) //Fila 31 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 232);
			if (multiplier == 4) { multiplier = 11; }
			if (multiplier == 12) { multiplier = 14; }
			if (multiplier == 15) { multiplier = 24; }
			++App->particles->COUNTDOWN;

		};
		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 32 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 240);
			if (multiplier == 4) { multiplier = 11; }
			if (multiplier == 12) { multiplier = 14; }
			if (multiplier == 15) { multiplier = 24; }
			++App->particles->COUNTDOWN;
		};

		for (multiplier = 4; multiplier <= 25; ++multiplier) //Fila 33 P1
		{
			App->particles->AddParticle(App->particles->pacdot, 8 * multiplier, 248);
			if (multiplier == 12) { multiplier = 14; }
			++App->particles->COUNTDOWN;
		}; 
	

	App->enemies->AddEnemy(Enemy_Type::BLINKY, 112, 136);
	

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

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 15;

	if (App->particles->COUNTDOWN <= 0) 
	{
		LOG("VICTORY");
		App->fade->FadeToBlack(this, (Module*)App->win, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg", 1.0f);
	
	}
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
