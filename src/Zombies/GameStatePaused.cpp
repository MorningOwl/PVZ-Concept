#include "pch.h"
#include "GameStatePaused.h"

#include "Game.h"


GameStatePaused::GameStatePaused()
{
	m_Text = bn::Font(Game::Get()->GetTextureManager().Get("Basic_Font"));
	m_Text.SetText("paused");
	m_Text.SetPosition(350, 290);

	sprite.SetTexture(Game::Get()->GetTextureManager().Get("Plant_Zombie"));
}

void GameStatePaused::HandleInput()
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
					case (int)bn::Key::Enter:
					case (int)bn::Key::Escape:
						Game::Get()->PopState();
						break;
				}
		}
	}
}

void GameStatePaused::Update(float dt)
{

}

void GameStatePaused::Draw()
{
	m_Text.Draw(Game::Get()->GetRenderer());
}