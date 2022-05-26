
#pragma once

#include <SFML/Graphics/Color.hpp>

namespace Settings
{
	extern bool save(const char* fileName);
	extern bool load(const char* fileName);
	extern void defaults();

	namespace General
	{
		extern bool showImgui;
	}

	namespace Audio
	{
		extern bool muted;
		extern int volume;
		extern float pitch;
	}

	namespace Gameplay
	{
		extern bool autoplay;
		extern float autoplayDelay;

		extern bool checkGameInAdvance;

		extern bool continousGenerate;
		extern int blockModel;
	}

	namespace Aspect
	{
		extern bool animations;

		extern float appBackground[3];
		extern float pickupMargins[3];
		extern float textColor[3];

		extern float cellSolid[3];
		extern float cellPreview[3];
		extern float cellCompletion[3];
		extern float cellMargins[3];

		extern float tableOdd[3];
		extern float tableEven[3];
		extern float tableMajor[3];
		extern float tableMinor[3];

		extern void defaultValues();
	}
}

extern sf::Color toColor(float* p);
extern void setFloatColors(float* p, float r, float g, float b);
