#include "Ghost_Blynky.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"

Enemy_Blinky::Enemy_Blinky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
	
	currentAnim = &up;

	up.PushBack({ 162, 111, 16, 17 });
	up.PushBack({ 162, 111, 16, 18 });
	up.PushBack({ 162, 111, 16, 19 });
	up.PushBack({ 162, 111, 16, 20 });
	up.PushBack({ 162, 105, 16, 21 });
	up.PushBack({ 162, 111, 16, 20 });
	up.PushBack({ 162, 111, 16, 19 });
	up.PushBack({ 162, 111, 16, 18 });
	up.PushBack({ 162, 111, 16, 17 });
	up.speed = 0.1f;
	up.loop = true;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 66, 111, 16, 17 });
	down.PushBack({ 66, 111, 16, 18 });
	down.PushBack({ 66, 111, 16, 19 });
	down.PushBack({ 66, 105, 16, 20 });
	down.PushBack({ 66, 105, 16, 21 });
	down.PushBack({ 66, 105, 16, 21 });
	down.PushBack({ 66, 105, 16, 20 });
	down.PushBack({ 66, 111, 16, 19 });
	down.PushBack({ 66, 111, 16, 18 });
	down.PushBack({ 66, 111, 16, 17 });
	down.loop = true;
	down.speed = 0.1f;

	rigth.PushBack({ 114, 111, 16, 17 });
	rigth.PushBack({ 114, 111, 16, 18 });
	rigth.PushBack({ 114, 111, 16, 19 });
	rigth.PushBack({ 114, 111, 16, 20 });
	rigth.PushBack({ 114, 105, 16, 21 });
	rigth.PushBack({ 114, 105, 16, 21 });
	rigth.PushBack({ 114, 111, 16, 20 });
	rigth.PushBack({ 114, 111, 16, 19 });
	rigth.PushBack({ 114, 111, 16, 18 });
	rigth.PushBack({ 114, 111, 16, 17 });
	//rigth.pingpong = true;
	rigth.loop = true;
	rigth.speed = 0.1f;

	left.PushBack({ 18, 111, 16, 17 });
	left.PushBack({ 18, 111, 16, 18 });
	left.PushBack({ 18, 111, 16, 19 });
	left.PushBack({ 18, 111, 16, 20 });
	left.PushBack({ 18, 105, 16, 21 });
	left.PushBack({ 18, 105, 16, 21 });
	left.PushBack({ 18, 111, 16, 20 });
	left.PushBack({ 18, 111, 16, 19 });
	left.PushBack({ 18, 111, 16, 18 });
	left.PushBack({ 18, 111, 16, 17 });
	left.loop = true;
	left.speed = 0.1f;

	

	////TODO: PROGRAMAR EL MOVIMIENTO DEL FANTASMA, EN ESTE CASO ES UNA IA SUPER BASICA
	
	
	
	//float repeater = 1;
	//path.PushBack({ 0.0f, -0.5f }, 65, &up); //A
	//path.PushBack({ 0.5f, 0.0f }, 150, &rigth);//B
	//path.PushBack({ 0.0f, 0.5f }, 150, &down);
	//path.PushBack({ -0.5f, 0.0f }, 120, &left);
	//path.PushBack({ 0.0f, 0.5f }, 45, &down);
	//path.PushBack({ -0.5f, 0.0f }, 60, &left);
	//path.PushBack({ 0.0f, -0.5f }, 45, &up);
	//path.PushBack({ -0.5f, 0.0f }, 120, &left);
	//path.PushBack({ 0.0f, -0.5f }, 150, &up);
	//path.PushBack({ 0.5f, 0.0f }, 150, &rigth);//-B
	//path.PushBack({ 0.0f, 0.5f }, 65, &down); //-A
	
	//path.PushBack({ 0.0f,0.0f }, 5, &up);

	 currentDirection = UP;
	 currentMode = CHASE;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Blinky::Update()
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation(); //hacer paths de 0 speed para cambiar la anim

	
	//TILE UPDATER (tile.x coresponds to height and tile .y corresponds to lenght)
	if ((int)position.x % 8 == 0)
	{
		tile.y = (position.x / 8);
	}
	if ((int)position.y % 8 == 0)
	{
		tile.x = (position.y / 8);
	}

	tileUp.x = tile.x - 1;
	tileUp.y = tile.y;

	tileDown.x = tile.x + 2;
	tileDown.y = tile.y;

	tileLeft.x = tile.x;
	tileLeft.y = tile.y - 1;

	tileRight.x = tile.x;
	tileRight.y = tile.y + 2;

	switch (currentMode)
	{
	case Enemy_Blinky::CHASE:

		objectives = App->player->position;
		switch (currentDirection)
		{
		case Enemy_Blinky::UP:
			if (App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileUp.x][tileUp.y + 1] == App->sceneLevel_1->GHOST)
			{
				position.y = -Movementspeed;
				LOG("%f,%f", position.x, position.y);
			}
			else
				 newDir = rand() % 2;
			switch (newDir)
			{
			case(0):
				currentDirection = LEFT;
				break;
			case(1):
				currentDirection = RIGTH;
				break;
			
			}
			break;
		
				
		case Enemy_Blinky::LEFT:

			if (App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->GHOST)
			{
				position.x =- Movementspeed;
				LOG("%f,%f",position.x,position.y);
			}
			else
				newDir = rand() % 2;
			LOG("New direction is %d", newDir);
			switch (newDir)
			{
			case(0):
				currentDirection = UP;
				break;
			case(1):
				currentDirection = DOWN;
				break;

			}
			break;
		case Enemy_Blinky::DOWN:

			if (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileDown.x][tileDown.y + 1] == App->sceneLevel_1->GHOST)
			{
				position.y =+ Movementspeed;
				/*LOG("Muevete");*/
			}
			else
				newDir = rand() % 2;
			switch (newDir)
			{
			case(0):
				currentDirection = LEFT;
				break;
			case(1):
				currentDirection = RIGTH;
				break;

			}
			break;
		case Enemy_Blinky::RIGTH:

			if (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileRight.x][tileRight.y + 1] == App->sceneLevel_1->GHOST)
			{
				position.x =+ Movementspeed;
				/*LOG("Muevete");*/
			}
			else
				newDir = rand() % 2;
			switch (newDir)
			{
			case(0):
				currentDirection = UP;
				break;
			case(1):
				currentDirection = DOWN;
				break;

			}
			break;
		default:
			break;
		}
		
		break;
	case Enemy_Blinky::SCATTER:


		break;
	case Enemy_Blinky::FEAR:

		LOG("panik activated");
		

		break;
	case Enemy_Blinky::EATEN:
		break;
	default:
		break;
	}

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->render->Blit(texture, (int)position.x, (int)position.y, &rect);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
