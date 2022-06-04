#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/PacDotsyPellets2.png");
	/*PowerPellet= App->textures->Load("Assets/Sprites/PowerUp.png");*/

	

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30}); 
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laser.anim.PushBack({ 232, 103, 16, 12 });
	laser.anim.PushBack({ 249, 103, 16, 12 });
	laser.speed.x = 5;
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;

	
	//saltan demasiado
		
	pacdot.anim.PushBack({ 0, 0, 5, 15 });
	pacdot.anim.PushBack({ 7, 0, 5, 15 });
	pacdot.anim.PushBack({ 15, 0, 5, 15 });
	pacdot.anim.PushBack({ 22, 0, 5, 15 });
	pacdot.anim.PushBack({ 29, 0, 5, 15 });
	pacdot.anim.PushBack({ 37, 0, 5, 15 });
	pacdot.anim.PushBack({ 44, 0, 5, 15 });
	pacdot.anim.PushBack({ 51, 0, 5, 15 });
	pacdot.anim.pingpong = false;
	pacdot.anim.loop = true;
	pacdot.anim.speed = 0.2f;


	//Power pellet
	powerpellet.anim.PushBack({ 72,0,12,15 });
	powerpellet.anim.PushBack({ 93,0,12,15 });
	powerpellet.anim.PushBack({ 116,0,12,15 });
	powerpellet.anim.PushBack({ 136,0,12,15 });
	powerpellet.anim.PushBack({ 157,0,12,15 });
	powerpellet.anim.pingpong = true;
	powerpellet.anim.loop = false;
	powerpellet.anim.speed = 0.2f;


	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	int waka1 = App->audio->LoadFx("Assets/Fx/waka/wakka_wakka1.wav");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			App->audio->PlayFx(waka1, 0);

			--COUNTDOWN;
			delete particles[i];
			particles[i] = nullptr;
			break;
		}

	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}
