
#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*
	This class is responsible with managing every audio that plays in the game.
	It also renders the mute/unmute button, it is here as its simpler to understand.
*/
class Audio
{
private:
	static sf::SoundBuffer& goodPlacement();
	static sf::SoundBuffer& badPlacement();
	static sf::SoundBuffer& completetion();
	static sf::Sound& playingSound();

	static sf::Texture& muteTexture();
	static sf::Texture& volumeTexture();
	static sf::Sprite& audioSprite();

public:
	static void initialize();

	enum class effect { GoodPlacement, BadPlacement, Completetion };

	static void play(effect theEffect);

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

	static void updateState();
};
