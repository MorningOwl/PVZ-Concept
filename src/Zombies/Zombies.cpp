#include "pch.h"
#include "Zombies.h"

#include "Game.h"
#include "Plants.h"


Zombie::Zombie(bn::Texture& texture, bn::Vector2f pos)
	:m_State(ZombieState::WALKING), m_Health(10), m_Attack(1), m_isAlive(true), m_Target(nullptr)
{
	SetOrigin(0, 32);
	SetPosition(pos);
	SetSize(16, 64);
	SetVelocity({ -50, 0 });
	m_SightRange = bn::Circle(GetCentre(), 100);

	m_AnimHandler.Add("Walk", texture, bn::AnimType::FORWARD_CYCLE, { 64 * 3, 0 }, { 32, 64 }, 6, 2.0f);
	m_AnimHandler.Add("Eat", texture, bn::AnimType::FORWARD_CYCLE, { 64 * 3, 128 }, { 32, 64 }, 3, 1.0f);
	m_AnimHandler.Add("Die", texture, bn::AnimType::FORWARD_STOP, { 64 * 3, 64 }, { 32, 64 }, 4, 0.5f);
}

void Zombie::Update(float dt)
{
	if (m_isAlive)
		switch (m_State)
		{
			case ZombieState::WALKING:
				m_AnimHandler.Play("Walk");
				UpdatePosition(dt);
				LookForPlant();
				break;

			case ZombieState::EATING:
				Eat();
				break;
		}

	else if (m_AnimHandler.AnimationEnded("Die"))
		GetParent()->QueueRemoveChild(this);

	m_AnimHandler.Update(dt);
}

void Zombie::Draw(bn::Renderer& renderer) 
{
	m_AnimHandler.SetPosition(GetPosition());
	m_AnimHandler.Draw(renderer);
}

void Zombie::OnHit(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_isAlive = false;
		Hide();
		m_AnimHandler.Play("Die");
	}
}

void Zombie::LookForPlant()
{
	auto plants = GetParent()->GetChildren<Plant>();
	for (auto& plant : plants)
		if (plant->isVisible() && plant->GetPosition().y == GetPosition().y - 1 && GetPlantCollider().Intersects(plant->GetCollider()))
		{
			m_Target = plant;
			m_State = ZombieState::EATING;
			return;
		}
}

void Zombie::Eat()
{
	m_AnimHandler.Play("Eat");
	if (m_AnimHandler.FrameStarted(1))
		m_Target->OnHit(m_Attack);

	if (m_Target->isDead())
	{
		m_Target = nullptr;
		m_State = ZombieState::WALKING;
	}
}
