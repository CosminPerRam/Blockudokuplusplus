
#include "settings.h"

namespace Settings
{
	bool save(const char* fileName) {
		return true;
	}

	bool load(const char* fileName) {

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
	}
}

sf::Color toColor(float* p) {
	return { static_cast<sf::Uint8>(p[0] * 255), static_cast<sf::Uint8>(p[1] * 255), static_cast<sf::Uint8>(p[2] * 255) };
}

void setFloatColors(float* p, float r, float g, float b) {
	p[0] = r; p[1] = g; p[2] = b;
}