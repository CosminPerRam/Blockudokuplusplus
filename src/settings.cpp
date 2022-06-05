
#include "settings.h"
#include "utilities.h"

namespace Settings
{
	bool save(const char* fileName) {
		if (!Files::exists(fileName))
			Files::create(fileName);
		else
			Files::erase(fileName);

		std::stringstream sstream;

		General::save(sstream);
		Audio::save(sstream);
		Gameplay::save(sstream);
		Aspect::save(sstream);

		Files::append(sstream, fileName);

		return true;
	}

	bool load(const char* fileName) {
		if (!Files::exists(fileName))
			return false;

		std::stringstream sstream = Files::read(fileName);

		General::load(sstream);
		Audio::load(sstream);
		Gameplay::load(sstream);
		Aspect::load(sstream);

		return true;
	}

	void defaults() {
		General::defaultValues();
		Audio::defaultValues();
		Gameplay::defaultValues();
		Aspect::defaultValues();
	}

	namespace General
	{
		bool showImgui;

		bool vsync;
		int aalevel;

		void defaultValues() {
			showImgui = false;

			vsync = true;
			aalevel = 0;
		}

		void save(std::stringstream& sstream) {
			sstream << showImgui << " " << vsync << " " << aalevel << std::endl;
		}

		void load(std::stringstream& sstream) {
			sstream >> showImgui >> vsync >> aalevel;
		}
	}

	namespace Audio
	{
		bool muted;
		int volume;
		float pitch;

		void defaultValues() {
			muted = false;
			volume = 100;
			pitch = 1;
		}

		void save(std::stringstream& sstream) {
			sstream << muted << " " << volume << " " << pitch << std::endl;
		}

		void load(std::stringstream& sstream) {
			sstream >> muted >> volume >> pitch;
		}
	}

	namespace Gameplay
	{
		bool autoplay;
		float autoplayDelay;

		bool checkGameInAdvance;

		bool continousGenerate;
		int blockModel;
		unsigned customBlockSizeHeight, customBlockSizeWidth;
		bool customBlockStructure[5][5];

		void defaultValues() {
			autoplay = false; autoplayDelay = 1.f;

			checkGameInAdvance = false;

			continousGenerate = false;
			blockModel = -1;
			customBlockSizeHeight = 3, customBlockSizeWidth = 3;
			for (unsigned i = 0; i < 5; i++) {
				for (unsigned j = 0; j < 5; j++)
					customBlockStructure[i][j] = 0;
			}
		}

		void save(std::stringstream& sstream) {
			sstream << checkGameInAdvance << " " << continousGenerate << " " << blockModel << " ";
			sstream << customBlockSizeHeight << " " << customBlockSizeWidth << " ";
			for (unsigned i = 0; i < 5; i++) {
				for (unsigned j = 0; j < 5; j++)
					sstream << customBlockStructure[i][j] << " ";
			}
			sstream << std::endl;
		}

		void load(std::stringstream& sstream) {
			sstream >> checkGameInAdvance >> continousGenerate >> blockModel;
			sstream >> customBlockSizeHeight >> customBlockSizeWidth;
			for (unsigned i = 0; i < 5; i++) {
				for (unsigned j = 0; j < 5; j++)
					sstream >> customBlockStructure[i][j];
			}
		}
	}

	namespace Aspect
	{
		bool animations;

		float appBackground[3];
		float pickupMargins[3];
		float textColor[3];

		float cellSolid[3];
		float cellPreview[3];
		float cellCompletion[3];
		float cellMargins[3];

		float tableOdd[3];
		float tableEven[3];
		float tableMajor[3];
		float tableMinor[3];

		void defaultValues() {
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
		}

		void save(std::stringstream& sstream) {
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

		void load(std::stringstream& sstream) {
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
		}
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
