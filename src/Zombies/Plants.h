#pragma once
#include <Bones.h>


class Zombie;

class Plant : public bn::StaticBody
{
	public:
		Plant(bn::Texture& texture, bn::Vector2f pos);

		virtual void Update(float dt) override;
		virtual void Draw(bn::Renderer& renderer) override;

		bn::FloatRect GetCollider() const { return { GetPosition().x + 20, GetPosition().y, 20, GetSize().y }; }
		bool isDead() const { return !m_isAlive; }
		void OnHit(int damage);


	protected:
		enum class PlantState { IDLE, SHOOTING };

		void LookForZombie();
		virtual void Shoot() = 0;

		bn::AnimationHandler m_AnimHandler;
		bn::AudioPlayer m_AudioPlayer;
		PlantState m_State;
		Zombie* m_Target;
		bn::Circle m_SightRange;
		bool m_isAlive;
		int m_Health, m_Attack;
};


class PeaShooter : public Plant
{
	public:
		PeaShooter(bn::Texture& texture, bn::Vector2f pos);


	private:
		virtual void Shoot() override;
};


class DoubleShooter : public Plant
{
	public:
		DoubleShooter(bn::Texture& texture, bn::Vector2f pos);


	private:
		virtual void Shoot() override;
};


class Pea : public bn::KinematicBody
{
	public:
		Pea(bn::Texture& texture, bn::Vector2f pos);

		virtual void Update(float dt) override;
		virtual void Draw(bn::Renderer& renderer) override;


	private:
		bn::AnimatedSprite m_Sprite;
};