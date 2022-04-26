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

	// move upwards
	upAnim.PushBack({ 0, 0, 15, 16 }); // #1
	upAnim.PushBack({ 16, 0, 16, 16 }); // #2
	upAnim.PushBack({ 32, 0, 15, 16 }); // #3 
	upAnim.PushBack({ 32, 16, 15, 16 }); // #4
	upAnim.PushBack({ 16, 16, 16, 16 }); // #5
	upAnim.PushBack({ 0, 16, 15, 16 }); // #6
	upAnim.loop = true;
	upAnim.speed = 0.2f;

	// Move down
	downAnim.PushBack({ 128, 2, 15, 14 }); // #1
	downAnim.PushBack({ 144, 1, 15, 15 }); // #2
	downAnim.PushBack({ 160, 0, 15, 16 }); // #3
	downAnim.PushBack({ 176, 16, 15, 16 }); // #4
	downAnim.PushBack({ 160, 16, 15, 15 }); // #5
	downAnim.PushBack({ 144, 16, 15, 15 }); // #6
	downAnim.loop = true;
	downAnim.speed = 0.2f;

	// move upwards
	leftAnim.PushBack({ 0, 32, 15, 16 }); // #1
	leftAnim.PushBack({ 16, 32, 15, 16 }); // #2
	leftAnim.PushBack({ 33, 32, 14, 16 }); // #3
	leftAnim.PushBack({ 226, 0, 13, 16 }); // #4
	leftAnim.PushBack({ 208, 0, 15, 16 }); // #5
	leftAnim.PushBack({ 192, 0, 15, 16 }); // #6
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

	// move upwards
	rightAnim.PushBack({ 48, 16, 15, 16 }); // #1
	rightAnim.PushBack({ 64, 16, 15, 16 }); // #2
	rightAnim.PushBack({ 80, 16, 14, 16 }); // #3
	rightAnim.PushBack({ 96, 0, 12, 16 }); // #4
	rightAnim.PushBack({ 80, 0, 14, 16 }); // #5
	rightAnim.PushBack({ 64, 0, 14, 16 }); // #6
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

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

	position.x = 110;
	position.y = 200;
	tile.x = 15;
	tile.y = 29;
	App->sceneLevel_1->TileSet[tile.x][tile.y];
	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 14, 14 }, Collider::Type::PLAYER, this);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	

	//TODO ERIC: Bajar la velocidad siin que se detengan

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT/* && App->sceneLevel_1->TileSet[tile.x-1][tile.y]<=2*/) 
	
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT /*&& App->sceneLevel_1->TileSet[tile.x +1][tile.y] <= 2*/)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->sceneLevel_1->TileSet[tile.x][tile.y-1] <= 2)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->sceneLevel_1->TileSet[tile.x][tile.y+1] <= 2)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	//Update Tile Position

	tile.x=position.x/8;
	tile.y = position.y / 8;


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
