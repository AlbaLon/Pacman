#ifndef __SCENE_LEVEL2_H__
#define __SCENE_LEVEL2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel2 : public Module
{
public:
	//Constructor
	SceneLevel2(bool startEnabled);

	//Destructor
	~SceneLevel2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	enum TypesOfTiles //Alba (para el array)
	{
		WALL,
		GHOST,
		EMPTY,
		TP,
		DASH,


		MAX_TYPES
	};

	//TileSet del nivel

	const int TileX = 29;
	const int TileY = 38;



	//[3d la profundidad][la altura] [la longuitud] 

	int TileSet[2][38][29] = {
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,  //0 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//1 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//2 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//3 *
	 EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,	//4 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//5 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,   //6 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//7 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//8 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//9 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//10 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//11 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//12 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//13*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//14 *
	 WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,EMPTY,EMPTY,EMPTY,WALL ,WALL ,EMPTY,EMPTY,WALL, WALL, WALL, WALL,EMPTY,EMPTY, WALL ,WALL ,WALL ,	//15 *
	 TP   ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,GHOST,GHOST,GHOST,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP   ,	//16 *
	 TP   ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP   ,	//17 *
	 WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,	//18 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//19 *
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//20*
	 WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,	//21 *
	 TP   ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP   ,	//22 *
	 TP   ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP   ,	//23*
	 WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,	//24*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//25*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//26*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//27*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//28*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//29*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//30*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//31*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//32*
	 EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,EMPTY,EMPTY,	//33*
	 EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,WALL ,EMPTY,EMPTY,	//34*
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//35*
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//36*
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	//37*
	// 0      1      2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28

	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,
	};




};

#endif#pragma once
