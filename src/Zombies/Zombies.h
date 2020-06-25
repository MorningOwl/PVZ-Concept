#pragma once
#include <Bones.h>


class Plant;

class Zombie : public bn::KinematicBody
{
	public:
		Zombie(bn::Texture& texture, bn::Vector2f pos);

		virtual void Update(float dt) override;
		virtual void Draw(bn::Renderer& renderer) override;

		bn::FloatRect GetPlantCollider() const { return { GetPosition().x + 8, GetPosition().y, 32, 20 }; }
		bn::FloatRect GetLawnMowerCollider() const { return { GetPosition().x + 8, GetPosition().y + 32, 22, 32 }; }
		bool isDead() const { return !m_isAlive; }
		void OnHit(int damage);


	private:
		enum class ZombieState { WALKING, EATING };

		void LookForPlant();
		void Eat();

		ZombieState m_State;
		bn::AnimationHandler m_AnimHandler;
		int m_Health, m_Attack;
		bool m_isAlive;
		Plant* m_Target;
		bn::Circle m_SightRange;
};