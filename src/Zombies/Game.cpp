#include "pch.h"
#include "Game.h"

#include "GameStatePlaying.h"

#include <Bones/EntryPoint.h>


Game::Game(int width, int height, const char* title) : bn::BonesGame(width, height, title)
{
	GetTextureManager().Load("Grass", "assets/textures/Grass.png");
	GetTextureManager().Load("Plant_Zombie", "assets/textures/Plant_Zombie.png");
	GetTextureManager().Load("GUI", "assets/textures/GUI.png");
	GetTextureManager().Load("Basic_Font", "assets/fonts/Basic.png");

	GetMapDataManager().Load("Field", "assets/maps/Field.txt");

	GetSoundManager().Load("Shoot", "assets/sounds/pop1.wav");
	GetMusicManager().Load("Bugs", "assets/sounds/test1.wav");

	PushState(new GameStatePlaying);
}

Game::~Game()
{

}


bn::BonesGame* bn::CreateGame()
{
	return new Game(800, 600, "Plants Vs Zombies");
}