
#include "audio.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

bool Audio::initialized = false;
sf::SoundBuffer Audio::goodPlacement, Audio::badPlacement, Audio::completetion;
sf::Sound Audio::playingSound;

void Audio::initialize() {
	goodPlacement.loadFromFile("resources/goodPlacement.ogg");
	badPlacement.loadFromFile("resources/badPlacement.ogg");
	completetion.loadFromFile("resources/completetion.ogg");

	initialized = true;
}

void Audio::play(effect theEffect) {
	if (!initialized)
		return;

	switch (theEffect) {
	case effect::BadPlacement:
		playingSound.setBuffer(badPlacement);
		break;
	case effect::GoodPlacement:
		playingSound.setBuffer(goodPlacement);
		break;
	case effect::Completetion:
		playingSound.setBuffer(completetion);
		break;
	}

	playingSound.play();
}