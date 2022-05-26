
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
		Aspect::defaultValues();
	}

	namespace General
	{
		bool showImgui = false;
	}

	namespace Audio
	{
		bool muted = false;
		int volume = 100;
		float pitch = 1;
	}

	namespace Gameplay
	{
		bool autoplay = false;
		float autoplayDelay = 1;

		bool checkGameInAdvance = false;

		bool continousGenerate = false;
		int blockModel = -1;
	}

	namespace Aspect
	{
		bool animations = true;

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