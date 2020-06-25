#include "pch.h"
#include "Player.h"

#include "Game.h"
#include "Plants.h"


bn::Sprite Player::m_Sprite;
Player::PlayerState Player::m_State = Player::PlayerState::IDLE;
Player::PlantType Player::m_Type = Player::PlantType::PEASHOOTER;
//bn::RectangleShape Player::m_Shape;
bool Player::m_CanPlace = false;

void Player::Init()
{
	m_Sprite.SetTexture(Game::Get()->GetTextureManager().Get("Plant_Zombie"));
	m_Sprite.SetTextureRect({ 0, 0, 64, 64 });
	m_Sprite.SetOrigin(16, 32);
	m_Sprite.SetAlpha(100);

	//m_Shape.SetSize(32, 32);
	//m_Shape.SetColour(255, 255, 255, 25);
}

void Player::Update()
{
	auto map = Game::Get()->CurrentScene()->GetChild<bn::TileMap>();
	auto tiles = map->GetTileRects();
	auto mousepos = bn::Input::GetMousePosition();
	m_CanPlace = !map->GetTile(mousepos)->isCollidable();

	switch (m_State)
	{
		case PlayerState::PLACING:
			if (m_CanPlace && map->GetBounds().Contains(mousepos))
			{
				for (auto& tile : tiles)
					if (tile.Contains(mousepos))
					{
						m_Sprite.SetPosition(tile.x, tile.y - 1);
						//m_Shape.SetPosition(tile.x, tile.y - 1);
						break;
					}

				if (bn::Input::wasMouseButtonPressed(bn::MouseButton::Left))
				{
					switch (m_Type)
					{
						case PlantType::PEASHOOTER:
							Game::Get()->CurrentScene()->QueueAddChild(new PeaShooter(Game::Get()->GetTextureManager().Get("Plant_Zombie"), m_Sprite.GetPosition() - bn::Vector2f(16, 32)));
							break;

						case PlantType::DOUBLESHOOTER:
							Game::Get()->CurrentScene()->QueueAddChild(new DoubleShooter(Game::Get()->GetTextureManager().Get("Plant_Zombie"), m_Sprite.GetPosition() - bn::Vector2f(16, 32)));
							break;
					}

					
					m_State = PlayerState::IDLE;
					map->GetTile(mousepos)->SetCollision(true);
				}
			}

			if (Game::Get()->CurrentScene()->GetChild<bn::GUI>()->wasButtonPressed("PeaShooter"))
				m_State = PlayerState::IDLE;

			break;

		case PlayerState::IDLE:
			if (Game::Get()->CurrentScene()->GetChild<bn::GUI>()->wasButtonPressed("PeaShooter"))
				m_Sprite.SetTextureRect({ 0, 0, 64, 64 }), m_State = PlayerState::PLACING, m_Type = PlantType::PEASHOOTER;
			
			else if (Game::Get()->CurrentScene()->GetChild<bn::GUI>()->wasButtonPressed("DoubleShooter"))
				m_Sprite.SetTextureRect({ 0, 64 * 3, 64, 64 }), m_State = PlayerState::PLACING, m_Type = PlantType::DOUBLESHOOTER;

			break;
	}

	std::string text = "";
	text += "this is a test for the renderer\n";
	text += "just to make sure the performance is\n";
	text += "looking good since each character is\n";
	text += "rendered as a separate quad it would\n";
	text += "be quite nice if everything runs smoothly\n";
	text += "as i was a bit concerned about the effect\n";
	text += "of too many draw calls on the overall\n";
	text += "performance of the engine and the games\n";
	text += "i make using it\n";
	text += "words words words words words words words\n";
	text += "words words words words words words words\n";
	text += "words words words words words words words\n";

	//Game::Get()->CurrentScene()->GetChild<bn::GUI>()->GetText("Player_Health")->SetText(text);
}

void Player::Draw(bn::Renderer& renderer)
{
	switch (m_State)
	{
		case PlayerState::PLACING:
			if (m_CanPlace)
			{
				//renderer.Draw(m_Shape);
				Game::Get()->GetRenderer().Draw(m_Sprite);
			}
			break;

		case PlayerState::IDLE:
			break;
	}

}