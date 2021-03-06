#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"
#include "ModuleTextures.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	// ERIC: MODIFICADO, COLLIDER CHOCA CON PLAYER PERO NO AL REVES 
	matrix[Collider::Type::GHOST_EATER][Collider::Type::GHOST_EATER] = false;
	matrix[Collider::Type::GHOST_EATER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::GHOST_EATER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::GHOST_EATER][Collider::Type::PACDOT] = false;
	matrix[Collider::Type::GHOST_EATER][Collider::Type::POWERPELLET] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::GHOST_EATER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PACDOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::POWERPELLET] = false; //If players colides it gets destroyed, so it's the power pellet the one that collides

	matrix[Collider::Type::ENEMY][Collider::Type::GHOST_EATER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PACDOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POWERPELLET] = false;

	matrix[Collider::Type::PACDOT][Collider::Type::GHOST_EATER] = true;
	matrix[Collider::Type::PACDOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PACDOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PACDOT][Collider::Type::PACDOT] = false;
	matrix[Collider::Type::PACDOT][Collider::Type::POWERPELLET] = false;

	matrix[Collider::Type::POWERPELLET][Collider::Type::GHOST_EATER] = true;
	matrix[Collider::Type::POWERPELLET][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWERPELLET][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWERPELLET][Collider::Type::PACDOT] = false;
	matrix[Collider::Type::POWERPELLET][Collider::Type::POWERPELLET] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	


	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) //SHOW COLIDERS
		debug = !debug;
	

	;

	return Update_Status::UPDATE_CONTINUE;
}



Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::GHOST_EATER: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PACDOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::POWERPELLET: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

bool ModuleCollisions::Destroy(Collider* col)
{
	if (col != nullptr)
	{
		delete col;
		col = nullptr;
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
