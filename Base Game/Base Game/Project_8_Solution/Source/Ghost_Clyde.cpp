#include "Ghost_Clyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Clyde::Enemy_Clyde(int x, int y) : Enemy(x, y)
{//TODO: CUADRAR LA ANIMACION A LA SPRITE SHEET

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


	//TODO: PROGRAMAR EL MOVIMIENTO DEL FANTASMA, EN ESTE CASO ES UNA IA SUPER BASICA
	float repeater = 1;
	path.PushBack({ 0.0f, -0.5f }, 65, &up); //A
	path.PushBack({ 0.5f, 0.0f }, 150, &rigth);//B
	path.PushBack({ 0.0f, 0.5f }, 150, &down);
	path.PushBack({ -0.5f, 0.0f }, 120, &left);
	path.PushBack({ 0.0f, 0.5f }, 45, &down);
	path.PushBack({ -0.5f, 0.0f }, 60, &left);
	path.PushBack({ 0.0f, -0.5f }, 45, &up);
	path.PushBack({ -0.5f, 0.0f }, 120, &left);
	path.PushBack({ 0.0f, -0.5f }, 150, &up);
	path.PushBack({ 0.5f, 0.0f }, 150, &rigth);//-B
	path.PushBack({ 0.0f, 0.5f }, 65, &down); //-A



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