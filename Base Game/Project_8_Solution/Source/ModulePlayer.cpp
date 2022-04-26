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
	upAnim.PushBack({ 0, 0, 15, 16 }); //#1
	upAnim.PushBack({ 16, 0, 16, 16 }); // #2
	upAnim.PushBack({ 32, 0, 15, 16 }); // #3 
	upAnim.PushBack({ 32, 16, 15, 16 }); // #4
	upAnim.PushBack({ 16, 16, 16, 16 }); // #5
	upAnim.PushBack({ 0, 16, 15, 16 }); //#6
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
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT /*&& App->sceneLevel_1->TileSet[tile.x +1][tile.y] <= 2*/)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT /*&& App->sceneLevel_1->TileSet[tile.x][tile.y-1] <= 2*/)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT /*&& App->sceneLevel_1->TileSet[tile.x][tile.y+1] <= 2*/)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	//Update Tile Position

	tile.x;


	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) //ERIC:GOD MODE
	{
		if (inmortality == false)
			inmortality = true;
		else
		{
			inmortality = false;
		} 
			
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

		//TODO : Crear la escena de GAME OVER e ir a ella
		
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}