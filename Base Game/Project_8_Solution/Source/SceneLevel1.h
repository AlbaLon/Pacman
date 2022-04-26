#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

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

	int SizeTile = 32; //NO SE SI ES 32 O CUANTO

	enum TypesOfTiles //Alba (para el array)
	{
		WALL,
		GHOST,
		PACDOT,
		EMPTY,
		TP,

		MAX_TYPES
	};

	//TileSet del nivel

	int TileSet[29][38] = {
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,  //0
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//1
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//2
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//3
	 EMPTY ,EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY ,	//4
	 EMPTY ,EMPTY, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY ,	//5
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//6
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//7
	 WALL  ,EMPTY, EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL ,	//8
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//9
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//10
	 WALL  ,WALL,  WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL ,	//11
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//12
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//13
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, EMPTY,EMPTY,EMPTY,WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//14
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,GHOST,GHOST,GHOST,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//15
	 WALL  ,WALL,  WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL ,	//16
	 TP    ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP ,		//17
	 TP    ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TP ,		//18
	 WALL  ,WALL,  WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL ,	//19
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//20
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//21
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//22
	 EMPTY ,EMPTY, EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY ,	//23
	 WALL  ,WALL,  WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL ,	//24
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//25
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//26
	 WALL  ,EMPTY, EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL, EMPTY,EMPTY,WALL ,	//27
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//28
	 WALL  ,EMPTY, EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,WALL, WALL, WALL, WALL, EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,WALL ,	//29
	 WALL  ,WALL,  WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, WALL, WALL ,	//30
	 EMPTY ,EMPTY, WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL, EMPTY,EMPTY ,	//31
	 EMPTY ,EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY,EMPTY ,	//32
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//33
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//34
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//35
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//36
	};
	//0		1		2		3	4		5	6		7	8		9	10		11	12		13	14		15	16		17	18		19	20	21		22		23	24		25	26		27	28

};

#endif