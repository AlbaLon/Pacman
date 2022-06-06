#include "Ghost_Pinky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Pinky::Enemy_Pinky(int x, int y) : Enemy(x, y)
{//TODO: CUADRAR LA ANIMACION A LA SPRITE SHEET

	//ALBA: ANIMAR
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

	currentAnim = &up;
	



	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Pinky::Update()
{
	/*path.Update();*/
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}