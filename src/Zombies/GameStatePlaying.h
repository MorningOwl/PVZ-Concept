#pragma once
#include <Bones.h>


class GameStatePlaying : public bn::PlayingState
{
	public:
		GameStatePlaying();

		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

		//bn::Font f1;
};