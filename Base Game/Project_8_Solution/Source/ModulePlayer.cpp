#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite //TODO: Animar a pacman
	idleAnim.PushBack({ 66, 1, 14, 14 });

	//SI ES SIEMPRE 16x16 mejor para que cuadre la size de la grid con la de la animación.

	// move upwards
	upAnim.PushBack({ 0, 0, 16, 16 }); //#1
	upAnim.PushBack({ 16, 0, 16, 16 }); // #2
	upAnim.PushBack({ 32, 0, 16, 16 }); // #3 
	upAnim.PushBack({ 32, 16, 16, 16 }); // #4
	upAnim.PushBack({ 16, 16, 16, 16 }); // #5
	upAnim.PushBack({ 0, 16, 16, 16 }); //#6
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	// move upwards
	leftAnim.PushBack({ 100, 1, 32, 14 });
	leftAnim.PushBack({ 132, 0, 32, 14 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	// move upwards
	rigthAnim.PushBack({ 100, 1, 32, 14 });
	rigthAnim.PushBack({ 132, 0, 32, 14 });
	rigthAnim.loop = false;
	rigthAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Pac-man.png"); //ERIC: Ya subido
	currentAnimation = &idleAnim;

	/*laserFx = App->audio->LoadFx("Assets/Fx/laser.wav"); //NO USAMOS ESTOS SONIDOS PERO PARA SABER COMO SE PONEN
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");*/
	tileDL.x = 14; //14 26
	tileDL.y = 25;

	position.x = 8*tileDL.x ;
	position.y = 8*tileDL.y ;
	
	App->sceneLevel_1->TileSet[tileDL.x][tileDL.y];
	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 16, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	

	//TODO ERIC: Bajar la velocidad siin que se detengan
	// 
	
	//Update Tile Position

	tileDL.x=position.x/8;
	tileDL.y = position.y / 8;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT  )
	{
		if (((int)position.x%8)==0)
		{
			if (App->sceneLevel_1->TileSet[tileDL.x - 1][tileDL.y] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[tileDL.x - 1][tileDL.y + 1] == App->sceneLevel_1->EMPTY)
			{
				position.x -= speed;
				tileDL.x = position.x / 8;
			}
		}
		
		else 
		{
			position.x -= speed;
		}
		
		//position.x -= 8;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT  )
	{
		if (((int)position.x % 8) == 0)
		{ 
		if (App->sceneLevel_1->TileSet[tileDL.x +2][tileDL.y] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[tileDL.x + 2][tileDL.y+1] == App->sceneLevel_1->EMPTY){}
		{
			position.x += speed;
			tileDL.x = position.x / 8;
		}
		}
		else
		{
			position.x += speed;
		}
		//position.x += 8;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT )
	{
		if (((int)position.y % 8) == 0)
		{
		if (App->sceneLevel_1->TileSet[tileDL.x][tileDL.y-1] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[tileDL.x + 1][tileDL.y-1] == App->sceneLevel_1->EMPTY)
		position.y += speed;
		}
		else 
		{
			position.y += speed;
			tileDL.y = position.y / 8;
		}
		//position.y += 8;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT  )
	{
		
		if (((int)position.y % 8) == 0)
		{
			if (App->sceneLevel_1->TileSet[tileDL.x][tileDL.y + 2] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[tileDL.x + 2][tileDL.y + 1] == App->sceneLevel_1->EMPTY)
			{
				position.y -= speed;
				tileDL.y = position.y / 8;
			}
		}
		else 
		{
			position.y -= speed;
		}
		//position.y -= 8;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	


	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) //ERIC:GOD MODE
	{
		if (inmortality == false)
			inmortality = true;
		else
		{
			inmortality = false;
		} 
			
	};

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) //ERIC: boton de muerte
	{
		inmortality = false;
		collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 14, 14 }, Collider::Type::ENEMY, this);

	};

	collider->SetPos((int)position.x, (int)position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, (int)position.x, (int)position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && inmortality==false)
	{
		//TODO animacion de muerte, ha de girar y luego particulas de estrellitas [https://youtu.be/IcZZtIcdrA4?t=20]
		App->particles->AddParticle(App->particles->explosion, (int)position.x - 4, (int)position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		//death animation
		//ERIC: Recuerda destruir el collider al morir
		deathAnim.PushBack({ 15, 0, 16, 16 }); //#1
		deathAnim.PushBack({ 239, 0, 16, 16 }); //#2
		deathAnim.PushBack({ 207, 0, 16, 16 }); //#3
		deathAnim.PushBack({ 175, 0, 16, 16 }); //#4
		deathAnim.PushBack({ 143, 0, 16, 16 }); //#5
		deathAnim.PushBack({ 111, 0, 16, 16 }); //#6
		deathAnim.PushBack({ 79, 0, 16, 16 }); //#7
		deathAnim.PushBack({ 15, 0, 16, 16 }); //#8
		deathAnim.PushBack({ 239, 0, 16, 16 }); //#9
		deathAnim.PushBack({ 207, 0, 16, 16 }); //#10
		deathAnim.PushBack({ 175, 0, 16, 16 }); //#11
		deathAnim.PushBack({ 159, 0, 16, 16 }); //#12
		deathAnim.PushBack({ 191, 16, 16, 16 }); //#13
		deathAnim.PushBack({ 208, 16, 16, 16 }); //#14
		deathAnim.PushBack({ 224, 16, 16, 16 }); //#15
		deathAnim.PushBack({ 239, 16, 16, 16 }); //#16
		deathAnim.loop = false;
		deathAnim.speed = 0.1f;


		//TODO : Crear la escena de GAME OVER e ir a ella
		
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}