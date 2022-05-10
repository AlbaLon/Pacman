#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_Mech.h"
#include "Ghost_Blynky.h"
#include "Ghost_Pinky.h"
#include "Ghost_Inky.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	//TODO: CARGAR LOS SPRITES DE PINKY, CLYDE Y KINKY
	Red_Ghost = App->textures->Load("Assets/Sprites/Blinky.png"); 
	Blue_Ghost = App->textures->Load("Assets/Sprites/Inky.png");
	Pink_Ghost = App->textures->Load("Assets/Sprites/Pinky.png"); //ERIC:PRUEBA, TENDRA QUE SER PINKY
	Orange_Ghost = App->textures->Load("Assets/Sprites/Clyde.png"); 
	Golden_Ghost = App->textures->Load("Assets/Sprites/Kinky.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			/*if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}*/
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::BLINKY:
				enemies[i] = new Enemy_Blinky(info.x, info.y);
				enemies[i]->texture = Red_Ghost;
				break;

			case Enemy_Type::PINKY:
				enemies[i] = new Enemy_Pinky(info.x, info.y);
				enemies[i]->texture = Pink_Ghost;
				break;

			case Enemy_Type::INKY:
				enemies[i] = new Enemy_Blinky(info.x, info.y);
				enemies[i]->texture = Blue_Ghost;
				break;

			case Enemy_Type::CLYDE:
				enemies[i] = new Enemy_Blinky(info.x, info.y);
				enemies[i]->texture = Orange_Ghost;
				break;

			case Enemy_Type::KINKY:
				enemies[i] = new Enemy_Blinky(info.x, info.y);
				enemies[i]->texture = Golden_Ghost;
				break;

			case Enemy_Type::BROWNSHIP:
				enemies[i] = new Enemy_BrownShip(info.x, info.y); //TODO: ELIMINAR AL FINAL
				break;
			case Enemy_Type::MECH:
				enemies[i] = new Enemy_Mech(info.x, info.y);
				break;
			}
			
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}