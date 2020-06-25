#pragma once
#include <Bones.h>


class Player
{
	public:
		static void Init();
		static void Update();
		static void Draw(bn::Renderer& renderer);


	private:
		enum class PlayerState { IDLE, PLACING };
		enum class PlantType { PEASHOOTER, DOUBLESHOOTER };

		static bn::Sprite m_Sprite;
		static PlayerState m_State;
		static PlantType m_Type;
		//static bn::RectangleShape m_Shape;
		static bool m_CanPlace;
};