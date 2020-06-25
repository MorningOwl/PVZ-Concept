#include "pch.h"
#include "GameStatePlaying.h"

#include "GameStatePaused.h"
#include "Game.h"
#include "Player.h"
#include "Levels.h"


GameStatePlaying::GameStatePlaying()
{
	Level1* level1 = new Level1("Field", Game::Get()->GetTextureManager().Get("Grass"), Game::Get()->GetMapDataManager().Get("Field"));
	GetRootObject()->AddChild(level1);
	Game::Get()->PushScene(level1);

	Player::Init();
}

void GameStatePlaying::HandleInput()
{
	static bn::Event ev;

	while (bn::EventHandler::PollEvents(ev))
	{
		switch (ev.type)
		{
			case bn::EventType::WindowClosed:
				Game::Get()->GetWindow()->Close();
				break;
				
			case bn::EventType::KeyPressed:
				switch (ev.keycode)
				{
					case (int)bn::Key::Escape:
						Game::Get()->GetWindow()->Close();
						break;

					case (int)bn::Key::Enter:
						Game::Get()->PushState(new GameStatePaused);
						break;
				}
				break;

			case bn::EventType::WindowFocus:
				if (ev.hasFocus)
					GetRootObject()->Enable();
				else
					GetRootObject()->Disable();
				break;
		}
	}
}

void GameStatePlaying::Update(float dt)
{
	GetRootObject()->Update(dt);
	Player::Update();
}

void GameStatePlaying::Draw()
{
	GetRootObject()->Draw(Game::Get()->GetRenderer());
	Player::Draw(Game::Get()->GetRenderer());
}