
#include "audio.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

bool Audio::initialized = false;

sf::SoundBuffer& Audio::goodPlacement() {
	static sf::SoundBuffer goodPlacement;
	return goodPlacement;
}

sf::SoundBuffer& Audio::badPlacement() {
	static sf::SoundBuffer badPlacement;
	return badPlacement;
}

sf::SoundBuffer& Audio::completetion() {
	static sf::SoundBuffer completetion;
	return completetion;
}

sf::Sound& Audio::playingSound() {
	static sf::Sound playingSound;
	return playingSound;
}

void Audio::initialize() {
	goodPlacement().loadFromFile("resources/goodPlacement.ogg");
	badPlacement().loadFromFile("resources/badPlacement.ogg");
	completetion().loadFromFile("resources/completetion.ogg");

	initialized = true;
}

void Audio::play(effect theEffect) {
	if (!initialized)
		return;

	switch (theEffect) {
	case effect::BadPlacement:
		playingSound().setBuffer(badPlacement());
		break;
	case effect::GoodPlacement:
		playingSound().setBuffer(goodPlacement());
		break;
	case effect::Completetion:
		playingSound().setBuffer(completetion());
		break;
	}

	playingSound().play();
}