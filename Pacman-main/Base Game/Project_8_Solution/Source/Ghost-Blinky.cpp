#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

//Enemy_Blinky::Enemy_Blinky(int x, int y) : Enemy(x, y)
//{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
//	front.PushBack({ 5, 108, 31, 29 });
//	front.PushBack({ 4, 141, 31, 29 });
//	front.PushBack({ 38, 108, 31, 29 });
//	front.speed = 0.1f;
//	//front.pingpong = true;
//
//	back.PushBack({ 170, 108, 31, 29 });
//	back.PushBack({ 170, 141, 31, 29 });
//	back.PushBack({ 137, 108, 31, 29 });
//	back.speed = 0.1f;
//	//back.pingpong = true;
//
//	path.PushBack({ -0.3f, 0.0f }, 150, &front);
//	path.PushBack({ 1.2f, 0.0f }, 150, &back);
//
//	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
//}
//
//void Enemy_Blinky::Update()
//{
//	path.Update();
//	position = spawnPos + path.GetRelativePosition();
//	currentAnim = path.GetCurrentAnimation();
//
//	// Call to the base class. It must be called at the end
//	// It will update the collider depending on the position
//	Enemy::Update();
//}
