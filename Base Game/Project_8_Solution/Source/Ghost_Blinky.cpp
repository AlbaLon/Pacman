#include "Ghost_Blynky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Blinky :: Enemy_Blinky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
	up.PushBack({ 161, 111, 31, 29 });
	up.PushBack({ 161, 105, 31, 29 });
	up.PushBack({ 161, 111, 31, 29 });
	up.speed = 0.1f;
	up.loop = true;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 65, 111, 31, 29 });
	down.PushBack({ 65, 105, 31, 29 });
	down.PushBack({ 65, 111, 31, 29 });
	down.loop = true;
	down.speed = 0.1f;

	rigth.PushBack({ 114, 111, 31, 29 });
	rigth.PushBack({ 114, 105, 31, 29 });
	rigth.PushBack({ 114, 111, 31, 29 });
	rigth.loop = true;
	rigth.speed = 0.1f;

	left.PushBack({ 18, 111, 31, 29 });
	left.PushBack({ 18, 105, 31, 29 });
	left.PushBack({ 18, 111, 31, 29 });
	left.loop = true;
	left.speed = 0.1f;

	
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
