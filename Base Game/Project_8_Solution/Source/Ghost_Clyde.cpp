#include "Ghost_Clyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Clyde::Enemy_Clyde(int x, int y) : Enemy(x, y)
{//TODO: CUADRAR LA ANIMACION A LA SPRITE SHEET

	//ALBA: ANIMAR
	up.PushBack({ 189, 79, 16, 17 });
	up.PushBack({ 189, 76, 16, 17 });
	up.PushBack({ 189, 79, 16, 17 });
	up.speed = 0.1f;
	up.loop = true;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 93, 79, 16, 17 });
	down.PushBack({ 93, 76, 16, 18 });
	down.PushBack({ 93, 79, 16, 17 });
	down.loop = true;
	down.speed = 0.1f;

	rigth.PushBack({ 141, 79, 16, 17 });
	rigth.PushBack({ 141, 76, 16, 17 });
	rigth.PushBack({ 141, 79, 16, 17 });
	//rigth.pingpong = true;
	rigth.loop = true;
	rigth.speed = 0.1f;

	left.PushBack({ 45, 79, 16, 17 });
	left.PushBack({ 45, 76, 16, 17 });
	left.PushBack({ 45, 79, 16, 17 });
	left.loop = true;
	left.speed = 0.1f;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Clyde::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}