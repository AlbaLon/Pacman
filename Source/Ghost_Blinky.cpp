#include "Ghost_Blynky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Blinky :: Enemy_Blinky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
	up.PushBack({ 5, 108, 31, 29 });
	up.PushBack({ 4, 141, 31, 29 });
	up.PushBack({ 38, 108, 31, 29 });
	up.speed = 0.1f;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 170, 108, 31, 29 });
	down.PushBack({ 170, 141, 31, 29 });
	down.PushBack({ 137, 108, 31, 29 });
	down.speed = 0.1f;
	
	//TODO: PROGRAMAR EL MOVIMIENTO DEL FANTASMA, EN ESTE CASO ES UNA IA SUPER BASICA
	/*path.PushBack({ -0.3f, 0.0f }, 150, &front);
	path.PushBack({ 1.2f, 0.0f }, 150, &back);*/

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Blinky::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
