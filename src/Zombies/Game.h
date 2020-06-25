#pragma once
#include <Bones.h>


class Game : public bn::BonesGame
{
	public:
		Game() {}
		Game(int width, int height, const char* title);
		~Game();
};