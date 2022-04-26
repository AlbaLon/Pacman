#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

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

	
	
	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL); //TODO: Eliminar cuando ya no sea necesario como comprovante 

	

	// Enemies ---
	//TODO: PONER A LOS DOS FANTASMAS EN SU SITIO 

	/*App->enemies->AddEnemy(Enemy_Type::REDBIRD, 600, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 665, 80);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);*/

	/*App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 3;

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
