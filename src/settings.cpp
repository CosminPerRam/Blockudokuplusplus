
#pragma once

#include "settings.h"
#include "utilities.h"
#include "game.h"

namespace Settings
{
	bool save(const char* fileName) {
		if (!Files::exists(fileName))
			Files::create(fileName);
		else
			Files::erase(fileName);

		std::stringstream sstream;

		Aspect::save(sstream);
		Audio::save(sstream);
		Gameplay::save(sstream);
		General::save(sstream);

		Files::append(sstream, fileName);

		return true;
	}

	bool load(const char* fileName) {
		if (!Files::exists(fileName))
			return false;

		std::stringstream sstream = Files::read(fileName);

		Aspect::load(sstream);
		Audio::load(sstream);
		Gameplay::load(sstream);
		General::load(sstream);

		return true;
	}

	void defaults() {
		General::defaultValues();
		Audio::defaultValues();
		Gameplay::defaultValues();
		Aspect::defaultValues();
	}

	void General::defaultValues() {
		showImgui = false;
		refreshRateImgui = 15;

		vsync = true;
		aalevel = 0;

		General::apply();
	}

	void General::save(std::stringstream& sstream) {
		sstream << showImgui << " " << refreshRateImgui << " " << vsync << " " << aalevel << std::endl;
	}

	void General::load(std::stringstream& sstream) {
		sstream >> showImgui >> refreshRateImgui >> vsync >> aalevel;

		General::apply();
	}

	void General::apply() {
		Game::updateAntialiasingSetting();
		Game::updateVsyncSetting();
		General::applyDataRefreshrate();
	}

	void General::applyDataRefreshrate() {
		if (Settings::General::refreshRateImgui < 1)
			Settings::General::refreshRateImgui = 1;
		if (Settings::General::refreshRateImgui > 999)
			Settings::General::refreshRateImgui = 999;
	}

	void Audio::defaultValues() {
		muted = false;
		volume = 100;
		pitch = 1;
	}

	void Audio::save(std::stringstream& sstream) {
		sstream << muted << " " << volume << " " << pitch << std::endl;
	}

	void Audio::load(std::stringstream& sstream) {
		sstream >> muted >> volume >> pitch;
	}

	void Gameplay::defaultValues() {
		autoplay = false; autoplayDelay = 1.f;

		checkGameInAdvance = false;

		continousGenerate = false;
		blockModel = -1;
		customBlockSizeHeight = 3, customBlockSizeWidth = 3;
		for (unsigned i = 0; i < 5; i++) {
			for (unsigned j = 0; j < 5; j++)
				customBlockStructure[i][j] = 0;
		}

		Gameplay::apply();
	}

	void Gameplay::save(std::stringstream& sstream) {
		sstream << checkGameInAdvance << " " << continousGenerate << " " << blockModel << " ";
		sstream << customBlockSizeHeight << " " << customBlockSizeWidth << " ";
		for (unsigned i = 0; i < 5; i++) {
			for (unsigned j = 0; j < 5; j++)
				sstream << customBlockStructure[i][j] << " ";
		}
		sstream << std::endl;
	}

	void Gameplay::load(std::stringstream& sstream) {
		sstream >> checkGameInAdvance >> continousGenerate >> blockModel;
		sstream >> customBlockSizeHeight >> customBlockSizeWidth;
		for (unsigned i = 0; i < 5; i++) {
			for (unsigned j = 0; j < 5; j++)
				sstream >> customBlockStructure[i][j];
		}

		Gameplay::apply();
	}

	void Gameplay::apply() {
		Gameplay::applyAutoplay();
		Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
	}

	void Gameplay::applyAutoplay() {
		if (Settings::Gameplay::autoplay)
			Settings::Gameplay::autoplay = false;

		if (Game::pickupBoard->isBoardLost())
			Game::theScore->setGameLost();
	}

	void Aspect::defaultValues() {
		animations = false;

		setFloatColors(appBackground, 1.f, 1.f, 1.f);
		setFloatColors(pickupMargins, 0.92f, 0.92f, 0.92f);
		setFloatColors(textColor, 0.f, 0.f, 0.f);

		setFloatColors(cellSolid, 0.21f, 0.72f, 1.f);
		setFloatColors(cellPreview, 0.69f, 0.89f, 1.f);
		setFloatColors(cellCompletion, 0.31f, 0.62f, 0.80f);
		setFloatColors(cellMargins, 0.f, 0.f, 0.f);

		setFloatColors(tableOdd, 0.92f, 0.92f, 0.92f);
		setFloatColors(tableEven, 1.f, 1.f, 1.f);
		setFloatColors(tableMajor, 0.f, 0.f, 0.f);
		setFloatColors(tableMinor, 0.69f, 0.89f, 1.f);

		Aspect::apply();
	}

	void Aspect::save(std::stringstream& sstream) {
		sstream << animations << " ";
		colorToStream(sstream, appBackground);
		colorToStream(sstream, pickupMargins);
		colorToStream(sstream, textColor);
		colorToStream(sstream, cellSolid);
		colorToStream(sstream, cellPreview);
		colorToStream(sstream, cellCompletion);
		colorToStream(sstream, cellMargins);
		colorToStream(sstream, tableOdd);
		colorToStream(sstream, tableEven);
		colorToStream(sstream, tableMajor);
		colorToStream(sstream, tableMinor);
		sstream << std::endl;
	}

	void Aspect::load(std::stringstream& sstream) {
		sstream >> animations;
		streamToColor(sstream, appBackground);
		streamToColor(sstream, pickupMargins);
		streamToColor(sstream, textColor);
		streamToColor(sstream, cellSolid);
		streamToColor(sstream, cellPreview);
		streamToColor(sstream, cellCompletion);
		streamToColor(sstream, cellMargins);
		streamToColor(sstream, tableOdd);
		streamToColor(sstream, tableEven);
		streamToColor(sstream, tableMajor);
		streamToColor(sstream, tableMinor);

		Aspect::apply();
	}

	void Aspect::apply() {
		Game::theTable->updateColors();
		Game::theScore->updateColors();
		Game::pickupBoard->updateColors();
	}
}

sf::Color toColor(float* c) {
	return { static_cast<sf::Uint8>(c[0] * 255), static_cast<sf::Uint8>(c[1] * 255), static_cast<sf::Uint8>(c[2] * 255) };
}

void setFloatColors(float* c, float r, float g, float b) {
	c[0] = r; c[1] = g; c[2] = b;
}

void colorToStream(std::stringstream& sstream, float* c) {
	sstream << c[0] << " " << c[1] << " " << c[2] << " ";
}

void streamToColor(std::stringstream& sstream, float* c) {
	sstream >> c[0] >> c[1] >> c[2];
}
