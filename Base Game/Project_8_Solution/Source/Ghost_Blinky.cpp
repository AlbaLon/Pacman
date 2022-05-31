#include "Ghost_Blynky.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_Blinky::Enemy_Blinky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
	
	

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
	
	
	
	

	 currentDirection = UP;
	 currentMode = CHASE;

	 
	 

	collider = App->collisions->AddCollider({ 0, 0, 8, 8 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Blinky::Update()
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation(); //hacer paths de 0 speed para cambiar la anim

	++timer;
	if (timer<1)
	{
	
	}
	
	
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

	if (changeTimer>=20)
	{changeLimit = false;}

		switch (currentMode)
		{
			
			
		case Enemy_Blinky::CHASE:

			objectives = App->player->position;
			++changeTimer;

			switch (currentDirection)
			{
				
				case Enemy_Blinky::UP:
				{
					
					//SEGUIR ADELANTE SI NO HAY PARED
					if (App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileUp.x][tileUp.y + 1] >= App->sceneLevel_1->GHOST)
					{
						position.y -= Movementspeed;
						currentAnim = &up;

					}

					//CAMBIAR DIRECCION EN UN CRUCE
					if ((App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit==false)
					{
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED UP");
						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = LEFT;
							LOG("Moving LEFT");
							
							break;
						}
					}

					if (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST && (int)position.x % 8 == 0
						&& (App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && changeLimit == false)
					{
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");
						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = RIGTH;
							LOG("Moving rigth");
							changeLimit = true;
							break;
						}
					}

					//CHOQUE CON PARED
					if ((App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
					{


						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							currentDirection = LEFT;
							LOG("Moving left");
							break;
						case(1):
							currentDirection = RIGTH;
							LOG("Moving rigth");
							break;

						}

						//Pared Izquierda--> Derecha
						if ((App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
						{
							currentDirection = RIGTH;
							LOG("Moving rigth");
						}
						//Pared Derecha--> Izquierda
						if ((App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
						{
							currentDirection = LEFT;
							LOG("Moving left");
						}


					}
					
					break;
				}

				
				case Enemy_Blinky::LEFT:
				{

					//SEGUIR ADELANTE SI NO HAY PARED
					if (App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST ||
						(App->sceneLevel_1->TileSet[tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
						(App->sceneLevel_1->TileSet[tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
						(App->sceneLevel_1->TileSet[tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
					{
						position.x -= Movementspeed;
						currentAnim = &left;
					}

					//CAMBIAR DIRECCION EN UN CRUCE
					if ((App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");

						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = UP;
							LOG("Moving rigth");
							break;
						}
					}

					if ((App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{

						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");

						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = DOWN;
							LOG("Moving rigth");
							break;
						}
					}

					//CHOQUE CON PARED
					if ((App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
					{



						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							currentDirection = UP;
							LOG("Moving up");
							break;
						case(1):
							currentDirection = DOWN;
							LOG("Moving down");
							break;
						}
						LOG("no se salto")
						//Pared alta--> Baja
						if ((App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
						{
							currentDirection = DOWN;
							LOG("Moving down");
						}
						//Pared bajo--> Alta
						if ((App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
						{
							currentDirection = UP;
							LOG("Moving up");
						}

					}
					break;
				}
			

				case Enemy_Blinky::DOWN:
				{

					//SEGUIR ADELANTE SI NO HAY PARED
					if (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileDown.x][tileDown.y + 1] >= App->sceneLevel_1->GHOST)
					{
						position.y += Movementspeed;
						currentAnim = &down;
				
					}

					//CAMBIAR DIRECCION EN UN CRUCE
					

					if ((App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");
						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = LEFT;
							LOG("Moving LEFT");
							break;
						}
					}

					if ((App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileLeft.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");

						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = RIGTH;
							LOG("Moving rigth");
							break;
						}
					}

					//CHOQUE CON PARED
					if (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
					{
				
						newDir = rand() % 2;
						switch (newDir)
						{
							case(0):
							currentDirection = LEFT;
							LOG("Moving left");
						break;
							case(1):
							currentDirection = RIGTH;
							LOG("Moving rigth");
						break;
						}
				
						//Pared Izquierda--> Derecha
						if (App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileLeft.x+ 1][tileLeft.y ] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
						{
							currentDirection = RIGTH;
							LOG("Moving rigth");
						}
						//Pared Derecha--> Izquierda
						if (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
						{
							currentDirection = LEFT;
							LOG("Moving left");
						}


					}
				break;
				}
		
				case Enemy_Blinky::RIGTH:
				{

					//SEGUIR ADELANTE SI NO HAY PARED
					if (App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST |
						(App->sceneLevel_1->TileSet[tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
						(App->sceneLevel_1->TileSet[tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
						(App->sceneLevel_1->TileSet[tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
					{
						position.x += Movementspeed;
						currentAnim = &rigth;
					}

					
					//CAMBIAR DIRECCION EN UN CRUCE
					 
					 

					if ((App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{					
						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");

						newDir = rand() % 2;
						switch (newDir)
						{
						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = UP;
							LOG("Moving rigth");
							break;
						}
					}

					if ((App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
						&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
					{

						changeLimit = true;
						changeTimer = 0;

						LOG("TRIGGERED");
						newDir = rand() % 2;
						switch (newDir)
						{

						case(0):
							//Continue going
							break;
						case(1):
							currentDirection = DOWN;
							LOG("Moving rigth");
							break;
						}
					}

					//CHOQUE CON PARED
					if ((App->sceneLevel_1->TileSet[tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
					{


						newDir = rand() % 2;
						switch (newDir)
						{
							case(0):
							currentDirection = UP;
							LOG("Moving up");
						break;
							case(1):
							currentDirection = DOWN;
							LOG("Moving down");
						break;
						}
						
						//Pared ARRIBA--> Baja
						if (App->sceneLevel_1->TileSet[tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
						{
							currentDirection = DOWN;
							LOG("Moving down");
						}
						//Pared abajo--> Sube
						if (App->sceneLevel_1->TileSet[tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
						{
							currentDirection = UP;
							LOG("Moving up");
						}
					}
				break;
				}
		
		
		
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
