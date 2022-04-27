//TODO (HAY EJEMPLOS DE LOS OTROS ENEMYS)

#include "Ghost_Inky.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Inky::Enemy_Inky(int x, int y) : Enemy(x, y)
{//TODO DEFINIRLO EN LOS PUSHBACKS Y ANIMATION Y PATH O LO QUE SEA
	up.PushBack({ 163, 103, 31, 29 });
	up.PushBack({ 163, 99, 31, 29 });
	up.PushBack({ 163, 103, 31, 29 });
	up.speed = 0.1f;
	up.loop = true;
	up.pingpong = true; //Esto hace que la animación vaya de adelante a atras y atras adelante, si la animacion es ciclica hay que poner el loop

	down.PushBack({ 63, 103, 31, 29 });
	down.PushBack({ 63, 99, 31, 29 });
	down.PushBack({ 63, 103, 31, 29 });
	down.loop = true;
	down.speed = 0.1f;

	//TODO: PROGRAMAR EL MOVIMIENTO DEL FANTASMA, EN ESTE CASO ES UNA IA SUPER BASICA
	/*path.PushBack({ -0.3f, 0.0f }, 150, &front);
	path.PushBack({ 1.2f, 0.0f }, 150, &back);*/

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Inky::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}