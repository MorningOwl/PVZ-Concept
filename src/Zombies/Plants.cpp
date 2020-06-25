#include "pch.h"
#include "Plants.h"

#include "Game.h"
#include "Zombies.h"


Plant::Plant(bn::Texture& texture, bn::Vector2f pos)
	:m_State(PlantState::IDLE), m_Target(nullptr), m_isAlive(true), m_Health(5), m_Attack(1)
{
	SetOrigin(16, 32);
	SetPosition(pos);
	SetSize(64);
	m_SightRange = { GetCentre(), 500 };
	m_AudioPlayer.AddSound("Shoot", Game::Get()->GetSoundManager().Get("Shoot"));
}

void Plant::Update(float dt)
{
	if (m_isAlive)
		switch (m_State)
		{
			case PlantState::IDLE:
				m_AnimHandler.Play("Idle");
				LookForZombie();
				break;

			case PlantState::SHOOTING:
				Shoot();
				break;
		}

	else if (m_AnimHandler.AnimationEnded("Die"))
	{
		GetParent()->QueueRemoveChild(this);
		Game::Get()->CurrentScene()->GetChild<bn::TileMap>()->GetTile(GetCentre())->SetCollision(false);
	}

	m_AnimHandler.Update(dt);
	GameObject::Update(dt);
}

void Plant::Draw(bn::Renderer& renderer) 
{
	m_AnimHandler.SetPosition(GetPosition());
	m_AnimHandler.Draw(renderer);
	GameObject::Draw(renderer);
}

void Plant::OnHit(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_isAlive = false;
		Hide();
		m_AnimHandler.Play("Die");
	}
}

void Plant::LookForZombie()
{
	auto zombies = GetParent()->GetChildren<Zombie>();
	for (auto& zombie : zombies)
		if (zombie->isVisible() && m_SightRange.Contains(zombie->GetPosition())
			&& zombie->GetPosition().y == GetPosition().y + 1 && zombie->GetPosition().x >= GetPosition().x + GetSize().x)
		{
			m_Target = zombie;
			m_State = PlantState::SHOOTING;
			return;
		}
}


PeaShooter::PeaShooter(bn::Texture& texture, bn::Vector2f pos)
	:Plant(texture, pos)
{
	m_AnimHandler.Add("Idle", texture, bn::AnimType::FORWARD_BACKWARD_CYCLE, { 0, 0 }, { 64, 64 }, 3, 1.0f);
	m_AnimHandler.Add("Shoot", texture, bn::AnimType::FORWARD_CYCLE, { 0, 64 }, { 64, 64 }, 3, 1.0f);
	m_AnimHandler.Add("Die", texture, bn::AnimType::FORWARD_STOP, { 0, 128 }, { 64, 64 }, 3, 0.5f);
}

void PeaShooter::Shoot()
{
	m_AnimHandler.Play("Shoot");
	if (m_AnimHandler.FrameStarted(1))
	{
		QueueAddChild(new Pea(Game::Get()->GetTextureManager().Get("Plant_Zombie"), GetPosition() + bn::Vector2f(54, 13)));
		m_AudioPlayer.PlaySound("Shoot");
	}

	auto zombies = GetParent()->GetChildren<Zombie>();
	auto peas = GetChildren<Pea>();
	for (auto& pea : peas)
	{
		for (auto& zombie : zombies)
			if (pea->GetBounds().Intersects(zombie->GetPlantCollider()))
			{
				QueueRemoveChild(pea);
				zombie->OnHit(m_Attack);
			}
	}

	if (m_Target->isDead() || m_Target->GetPosition().x + m_Target->GetSize().x < GetPosition().x)
	{
		m_Target = nullptr;
		m_State = PlantState::IDLE;
	}
}


DoubleShooter::DoubleShooter(bn::Texture& texture, bn::Vector2f pos)
	:Plant(texture, pos)
{
	m_AnimHandler.Add("Idle", texture, bn::AnimType::FORWARD_BACKWARD_CYCLE, { 0, 64 * 3 }, { 64, 64 }, 3, 1.0f);
	m_AnimHandler.Add("Shoot", texture, bn::AnimType::FORWARD_CYCLE, { 64, 64 }, { { 0, 64 * 4 }, { 64, 64 * 4 }, { 0, 64 * 4 }, { 64, 64 * 4 }, { 64 * 2, 64 * 4 } }, 5.0f / 3);
	m_AnimHandler.Add("Die", texture, bn::AnimType::FORWARD_STOP, { 0, 64 * 5 }, { 64, 64 }, 3, 0.5f);
}

void DoubleShooter::Shoot()
{
	m_AnimHandler.Play("Shoot");
	if (m_AnimHandler.FrameStarted(1) || m_AnimHandler.FrameStarted(3))
	{
		m_AudioPlayer.PlaySound("Shoot");
		QueueAddChild(new Pea(Game::Get()->GetTextureManager().Get("Plant_Zombie"), GetPosition() + bn::Vector2f(54, 13)));
	}

	auto zombies = GetParent()->GetChildren<Zombie>();
	auto peas = GetChildren<Pea>();
	for (auto& pea : peas)
	{
		for (auto& zombie : zombies)
			if (pea->GetBounds().Intersects(zombie->GetPlantCollider()))
			{
				QueueRemoveChild(pea);
				zombie->OnHit(m_Attack);
			}
	}

	if (m_Target->isDead() || m_Target->GetPosition().x + m_Target->GetSize().x < GetPosition().x)
	{
		m_Target = nullptr;
		m_State = PlantState::IDLE;
	}
}


Pea::Pea(bn::Texture& texture, bn::Vector2f pos)
{
	SetPosition(pos);
	SetSize(4);
	SetVelocity({ 150, 0 });
	m_Sprite = bn::AnimatedSprite(texture, { 64 * 5, 64 }, { 4, 4 }, 2, 0.5f);
}

void Pea::Update(float dt)
{
	UpdatePosition(dt);

	if (GetPosition().x > Game::Get()->GetWindow()->GetSize().x)
		GetParent()->QueueRemoveChild(this);

	m_Sprite.Update(dt);
}

void Pea::Draw(bn::Renderer& renderer) 
{
	m_Sprite.SetPosition(GetPosition());
	renderer.Draw(m_Sprite);
}