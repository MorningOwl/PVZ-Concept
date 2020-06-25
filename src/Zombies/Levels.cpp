#include "pch.h"
#include "Levels.h"

#include "Game.h"
#include "Plants.h"
#include "Zombies.h"
#include "Objects.h"


Level::Level(const std::string& name, bn::Texture& texture, std::stringstream& mapData)
	:bn::Scene(name, texture, mapData, true), m_TileMapOffset({ 64, 72 })
{

}


Level1::Level1(const std::string& name, bn::Texture& texture, std::stringstream& mapData)
	:Level(name, texture, mapData)
{
	GetChild<bn::TileMap>()->SetPosition(GetTileMapOffset());
	for (int i = 0; i < 14; i++)
		AddChild(new LawnMower(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 64, 72.0f + i * 32 }));

	bn::GUI* Gui = new bn::GUI();
	Gui->AddButton("PeaShooter", Game::Get()->GetTextureManager().Get("GUI"), { 0, 0 }, { 32, 48 }, { 64, 0 });
	Gui->AddButton("DoubleShooter", Game::Get()->GetTextureManager().Get("GUI"), { 0, 48 }, { 32, 48 }, { 64 + 32, 0 });
	Gui->AddText("Warning", "a huge wave of zombies is approaching", Game::Get()->GetTextureManager().Get("Basic_Font"), { 105, 290 }, { 16, 16 });
	AddChild(Gui);

	GetAudioPlayer()->AddMusic("Bugs", Game::Get()->GetMusicManager().Get("Bugs"));
	GetAudioPlayer()->PlayMusic("Bugs");
}

void Level1::Update(float dt)
{
	if (bn::Input::wasKeyPressed(bn::Key::A))
		GetAudioPlayer()->PlayMusic("Bugs");

	else if (bn::Input::wasKeyPressed(bn::Key::S))
		GetAudioPlayer()->PauseMusic("Bugs");

	else if (bn::Input::wasKeyPressed(bn::Key::D))
		GetAudioPlayer()->StopMusic("Bugs");

	if (SecondsReached(3))
		QueueAddChild(new Zombie(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 830, GetTileMapOffset().y + 32.0f * 3 }));

	else if (SecondsReached(6))
		QueueAddChild(new Zombie(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 830, GetTileMapOffset().y + 32.0f * 5 }));

	else if (SecondsReached(9))
		QueueAddChild(new Zombie(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 830, GetTileMapOffset().y + 32.0f * 7 }));

	else if (SecondsReached(12))
		for (int i = 3; i <= 9; i += 2)
			QueueAddChild(new Zombie(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 830, GetTileMapOffset().y + 32.0f * i }));

	else if (SecondsReached(15))
		GetChild<bn::GUI>()->ShowText("Warning");

	else if (SecondsReached(18))
		for (int i = 2; i <= 9; i++)
			QueueAddChild(new Zombie(Game::Get()->GetTextureManager().Get("Plant_Zombie"), { 830, GetTileMapOffset().y + 32.0f * i }));

	else if (SecondsReached(20))
		GetChild<bn::GUI>()->HideText("Warning");

	bn::Scene::Update(dt);
}