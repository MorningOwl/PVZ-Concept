#include "pch.h"
#include "Objects.h"

#include "Game.h"
#include "Zombies.h"


LawnMower::LawnMower(bn::Texture& texture, bn::Vector2f pos)
	:m_State(LawnMowerState::INACTIVE)
{
	m_Sprite.SetTexture(texture);
	m_Sprite.SetTextureRect({ 64 * 5, 16 * 5, 32, 32 });
	SetPosition(pos);
	SetSize(32, 32);
	SetVelocity(200, 0);
}

void LawnMower::Update(float dt)
{
	switch (m_State)
	{
		case LawnMowerState::ACTIVE:
			UpdatePosition(dt);

			for (auto& zombie : GetParent()->GetChildren<Zombie>())
				if (GetBounds().Intersects(zombie->GetLawnMowerCollider()))
					zombie->OnHit(5);

			if (GetPosition().x >= Game::Get()->GetWindow()->GetSize().x)
				GetParent()->QueueRemoveChild(this);

			break;

		case LawnMowerState::INACTIVE:
			for (auto& zombie : GetParent()->GetChildren<Zombie>())
				if (GetBounds().Intersects(zombie->GetLawnMowerCollider()))
					m_State = LawnMowerState::ACTIVE;
			break;
	}
}

void LawnMower::Draw(bn::Renderer& renderer) 
{
	m_Sprite.SetPosition(GetPosition());
	renderer.Draw(m_Sprite);
}