#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite //TODO: Animar a pacman
	idleAnim.PushBack({ 128, 2, 15, 14 }); // #1

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
	if (App->sceneLevel_1->IsEnabled()==true) { level = 0; }
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Pac-man.png"); //ERIC: Ya subido
	currentAnimation = &idleAnim;

	//Writing fonts
	char lookupTableLong[] = { "0123456789abcdefghijklmnopqrstuvwxyz!'?=:·./ " }; //Alba: Poner todos los caractyeres necesarios y ajustar la imagen
	whiteFont = App->fonts->Load("Assets/Fonts/whiteFont.png", lookupTableLong, 1); //TODO: Load Fuente //
	char lookupTableShort[] = "0123456789abcdefghijklmnopqrstuvwxyz!?·./ ";
	blueFont = App->fonts->Load("Assets/Fonts/cyanFont.png", lookupTableLong, 1); //Hay que ajustarla un poco
	yellowFont = App->fonts->Load("Assets/Fonts/yellowFont.png", lookupTableLong, 1); 


	/*laserFx = App->audio->LoadFx("Assets/Fx/laser.wav"); //NO USAMOS ESTOS SONIDOS PERO PARA SABER COMO SE PONEN
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");*/
	tile.y = 26;
	tile.x = 14;
	position.x = tile.x*8;
	position.y = tile.y*8;
	
	/*bool MovingUp=false;
	bool MovingDown=false;
	bool MovingLeft=true;
	bool MovingRight=false;*/
	
	App->sceneLevel_1->TileSet[tile.x][tile.y];
	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ (int)position.x+1, (int)position.y+1, 16, 16 }, Collider::Type::PLAYER, this);
	//POSICIONTILE = App->collisions->AddCollider({ (int)position.x + 1, (int)position.y + 1, 16, 16 }, Collider::Type::ENEMY_SHOT, this); //ERIC:POSICION DE LA TILE, CUANDO ESTA CARGADA NO CARGA EL SPRITE
	return ret;
}

Update_Status ModulePlayer::Update()
{


	//Update Tile Position
	//TODO HACER ESTO MAS COMPLEJO DETECTANDO PROXIMIDAD

	if ((int)position.x % 8 == 0   )
	{
		tile.y =  (position.x / 8);
					
			//LOG("Las tiles son %d,%d y sus posibilidades de arriba son: %d,abajo son: %d izquierda son: %d y derecha son: %d",tile.x,tile.y, App->sceneLevel_1->TileSet[tileUp.x][tileUp.y], App->sceneLevel_1->TileSet[tileDown.x][tileDown.y], App->sceneLevel_1->TileSet[tileLeft.x][tileLeft.y], App->sceneLevel_1->TileSet[tileRight.x][tileRight.y])
	}
	if ((int)position.y % 8 == 0)
	{
		tile.x = (position.y / 8);
	}

	//Movement posibilities
	//LAS X SON LA ALTURA DENTRO DEL TILESET MIENTAS QUE LAS Ys SON LA LONGUITUD
	tileUp.x = tile.x-1;
	tileUp.y = tile.y;

	tileDown.x = tile.x+2;
	tileDown.y = tile.y;

	tileLeft.x = tile.x;
	tileLeft.y = tile.y-1;

	tileRight.x = tile.x;
	tileRight.y = tile.y+2;
	

	 


	 //MOVIMIENTO IZQUIERDA
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT ||  MovingLeft == true)
	{
		 
		
		 //IT CAN MOVE INTO TP AN PAST IT
		if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileLeft.x+1][tileLeft.y] >= App->sceneLevel_1->EMPTY) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y+1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y+1] == App->sceneLevel_1->TP) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
		{
		MovingUp = false;
		 MovingDown = false;
		 MovingLeft = true;
		 MovingRight = false;
		position.x -= speed;	
		
		if (currentAnimation != &leftAnim)
		{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
		}

		}
		
	}

	//MOVIMIENTO DERECHA
	if ((App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) || MovingRight==true )
	{
		

		//IT CAN MOVE INTO TP AN PAST IT
		if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileRight.x+1][tileRight.y] >= App->sceneLevel_1->EMPTY) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y+1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y+1] == App->sceneLevel_1->TP) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
			(App->sceneLevel_1->TileSet[level][tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
		{	
		 MovingUp = false;
		 MovingDown = false;
		 MovingLeft = false;
		 MovingRight = true;
		position.x += speed;
		
		if (currentAnimation != &rightAnim)
		{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
		}

		}
			
	}

	//MOVIMIENTO ABAJO
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT ||  MovingDown == true)
	{
		

		if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y+1] >= App->sceneLevel_1->EMPTY )
		{
		 MovingUp = false;
		 MovingDown = true;
		 MovingLeft = false;
		 MovingRight = false;
		position.y += speed;	
		
		if (currentAnimation != &downAnim)
		{
					downAnim.Reset();
					currentAnimation = &downAnim;
		}

		}
		
	}

	//MOVIMIENTO ARRIBA
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || MovingUp == true)
	{

		
		if (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y+1] >= App->sceneLevel_1->EMPTY )
		{
		 MovingUp = true;
		 MovingDown = false;
		 MovingLeft = false;
		 MovingRight = false;
		position.y -= speed;
		
		if (currentAnimation != &upAnim)
		{
					upAnim.Reset();
					currentAnimation = &upAnim;
		}
		}
		
	}

		//Go to other side of map after using TP

		if (position.x <= -8)
		{
			position.x = 232;
		}
		if (position.x >= 236)
		{
			position.x = -4;
		}




		//God mode: Inmunity agaist ghosts
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
		//POSICIONTILE->SetPos(tile.y * 8, tile.x * 8); //ERIC: Actualizacion posicion Tile

		currentAnimation->Update();

		return Update_Status::UPDATE_CONTINUE;
}


Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, (int)position.x, (int)position.y, &rect);

		//TODO: ALBA: UI
		//App->fonts->BlitText( x , y, scoreFont,  scoreText)
		App->fonts->BlitText(50, 100, whiteFont, "0");
		App->fonts->BlitText(16, 16, blueFont, "303 love you");
		//App->fonts->BlitText(8, 151, scoreFont, scoreText);
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
