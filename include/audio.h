#pragma once

#include "impl.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Audio : Drawable, Eventer
{
private:
	static bool initialized, muted;

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
};
