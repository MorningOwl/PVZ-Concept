#pragma once
#include <Bones.h>


class Level : public bn::Scene
{
	public:
		Level(const std::string& name, bn::Texture& texture, std::stringstream& mapData);


	private:
		bn::Vector2f m_TileMapOffset;


	protected:
		bn::Vector2f GetTileMapOffset() const { return m_TileMapOffset; }
};


class Level1 : public Level
{
	public:
		Level1(const std::string& name, bn::Texture& texture, std::stringstream& mapData);

		virtual void Update(float dt) override;
};