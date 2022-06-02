#include "Ghost_Clyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Clyde::Enemy_Clyde(int x, int y) : Enemy(x, y)
{//TODO: CUADRAR LA ANIMACION A LA SPRITE SHEET

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
