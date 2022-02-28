#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Audio
{
private:
	static bool initialized;

	static sf::SoundBuffer& goodPlacement();
	static sf::SoundBuffer& badPlacement();
	static sf::SoundBuffer& completetion();

	static sf::Sound& playingSound();

public:
	enum class effect { GoodPlacement, BadPlacement, Completetion };

	static void initialize();

	static void play(effect theEffect);
};
