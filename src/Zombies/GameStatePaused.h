#pragma once
#include <Bones.h>


class GameStatePaused : public bn::GameState
{
	public:
		GameStatePaused();

		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;


	private:
		bn::Font m_Text;
		bn::Sprite sprite;
};