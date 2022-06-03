
#include "audio.h"
#include "spacing.h"
#include "settings.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

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

sf::Texture& Audio::muteTexture() {
	static sf::Texture muteTexture;
	return muteTexture;
}

sf::Texture& Audio::volumeTexture() {
	static sf::Texture volumeTexture;
	return volumeTexture;
}

sf::Sprite& Audio::audioSprite() {
	static sf::Sprite audioSprite;
	return audioSprite;
}

void Audio::initialize() {
	if(!goodPlacement().loadFromFile("resources/goodPlacement.ogg"))
		throw "Couldn't load goodPlacement sound";

	if(!badPlacement().loadFromFile("resources/badPlacement.ogg"))
		throw "Couldn't load badPlacement sound";

	if(!completetion().loadFromFile("resources/completetion.ogg"))
		throw "Couldn't load completetion sound";

	if (!volumeTexture().loadFromFile("resources/volume.png"))
		throw "Couldn't load volume texture";
		
	if (!muteTexture().loadFromFile("resources/mute.png"))
		throw "Couldn't load mute texture";

	volumeTexture().setSmooth(true);
	muteTexture().setSmooth(true);

	audioSprite().setPosition({ AUDIO_POSITION_X, AUDIO_POSITION_Y });
	audioSprite().setTexture(volumeTexture());
	audioSprite().setScale(0.48f, 0.48f);
	
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

void Audio::draw(sf::RenderWindow& window) {
	window.draw(audioSprite());
}

void Audio::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	if (theEvent.type == sf::Event::MouseButtonPressed && theEvent.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if (audioSprite().getGlobalBounds().contains(mousePosition))
		{
			Settings::Audio::muted = !Settings::Audio::muted;

			Audio::updateState();
		}
	}
}

void Audio::updateState() {
	playingSound().setPitch(Settings::Audio::pitch);

	if (Settings::Audio::muted) {
		playingSound().setVolume(0);
		audioSprite().setTexture(muteTexture());
	}
	else {
		playingSound().setVolume(static_cast<unsigned>(Settings::Audio::volume));
		audioSprite().setTexture(volumeTexture());
	}
}