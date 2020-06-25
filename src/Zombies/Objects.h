#pragma once
#include <Bones.h>


class LawnMower : public bn::KinematicBody
{
	public:
		LawnMower(bn::Texture& texture, bn::Vector2f pos);

		virtual void Update(float dt) override;
		virtual void Draw(bn::Renderer& renderer) override;


	private:
		enum class LawnMowerState { ACTIVE, INACTIVE };

		LawnMowerState m_State;
		bn::Sprite m_Sprite;
};