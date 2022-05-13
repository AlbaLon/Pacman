

#include "Ghost_Inky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Inky::Enemy_Inky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA //ALBA: ANIMAR
	up.PushBack({ 163, 103, 16, 17 });
	up.PushBack({ 163, 99, 16, 21 });
	up.PushBack({ 163, 103, 16, 17 });
	up.speed = 0.1f;
	up.loop = true;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 67, 103, 16, 17 });
	down.PushBack({ 67, 99, 16, 21 });
	down.PushBack({ 67, 103, 16, 17 });
	down.loop = true;
	down.speed = 0.1f;

	rigth.PushBack({ 115, 103, 16, 17 });
	rigth.PushBack({ 115, 99, 16, 21 });
	rigth.PushBack({ 115, 103, 16, 17 });
	rigth.loop = true;
	rigth.speed = 0.1f;

	left.PushBack({ 19, 103, 16, 17 });
	left.PushBack({ 19, 99, 16, 21 });
	left.PushBack({ 19, 103, 16, 17 });
	left.loop = true;
	left.speed = 0.1f;

	
	pathI.PushBack({ 0.0f, -0.5f }, 65, &up); //A
	pathI.PushBack({ 0.0f, 0.5f }, 65, &down);//La animacion sigue igual aunque se haya cambiado: ERIC

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Inky::Update()
{
	pathI.Update();
	position = spawnPos + pathI.GetRelativePosition();
	currentAnim = pathI.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}