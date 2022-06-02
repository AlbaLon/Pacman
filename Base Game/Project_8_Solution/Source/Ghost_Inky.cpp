

#include "Ghost_Inky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Inky::Enemy_Inky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA //ALBA: ANIMAR
		up.PushBack({ 144, 0, 16, 15 });
	up.PushBack({ 160, 0, 16, 15 });
	up.PushBack({ 176, 0, 16, 15 });
	up.speed = 0.1f;
	up.loop = false;
	up.pingpong = true;

	down.PushBack({ 64, 0, 16, 15 });
	down.PushBack({ 80, 0, 16, 15 });
	down.PushBack({ 96, 0, 16, 15 });
	down.speed = 0.1f;
	down.loop = false;
	down.pingpong = true;


	rigth.PushBack({ 96, 0, 16, 15 });
	rigth.PushBack({ 112, 0, 16, 15 });
	rigth.PushBack({ 128, 0, 16, 15 });
	rigth.speed = 0.1f;
	rigth.loop = false;
	rigth.pingpong = true;


	left.PushBack({ 0, 0, 16, 15 });
	left.PushBack({ 16, 0, 16, 15 });
	left.PushBack({ 32, 0, 16, 15 });
	left.speed = 0.1f;
	left.loop = false;
	left.pingpong = true;

	
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
