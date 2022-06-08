
#pragma once

#include <sstream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#define SETTINGS_FILENAME_DEFAULT "settings.ini"

namespace Settings
{
	unsigned save(const char* fileName);
	unsigned load(const char* fileName);
	void defaults();

	struct General
	{
		inline static bool showImgui;
		inline static unsigned refreshRateImgui;

		inline static bool vsync;
		inline static unsigned aalevel; //0 - None, 1 - 2x, 2 - 4x, 3 - 8x, 4 - 16x

		static void defaultValues();
		static void save(std::stringstream& sstream);
		static void load(std::stringstream& sstream);
		static void apply();

		static void applyDataRefreshrate();
	};

	struct Audio
	{
		inline static bool muted;
		inline static int volume;
		inline static float pitch;

		static void defaultValues();
		static void save(std::stringstream& sstream);
		static void load(std::stringstream& sstream);
	};

	struct Gameplay
	{
		inline static bool autoplay;
		inline static float autoplayDelay;

		inline static bool checkGameInAdvance, paintMode;

		inline static bool continousGenerate;
		inline static int blockModel;
		inline static unsigned customBlockSizeHeight, customBlockSizeWidth;
		inline static bool customBlockStructure[5][5];

		inline static bool holdToMove;

		static void defaultValues();
		static void save(std::stringstream& sstream);
		static void load(std::stringstream& sstream);
		static void apply();

		static void applyAutoplay();
	};

	struct Aspect
	{
		inline static bool animations;
		inline static bool showConsole;

		inline static float appBackground[3];
		inline static float pickupMargins[3];
		inline static float textColor[3];

		inline static float cellSolid[3];
		inline static float cellPreview[3];
		inline static float cellCompletion[3];
		inline static float cellMargins[3];

		inline static float tableOdd[3];
		inline static float tableEven[3];
		inline static float tableMajor[3];
		inline static float tableMinor[3];

		static void defaultValues();
		static void save(std::stringstream& sstream);
		static void load(std::stringstream& sstream);
		static void apply();
	};
}

sf::Color toColor(float* c);
void setFloatColors(float* c, float r, float g, float b);
void colorToStream(std::stringstream& sstream, float* c);
void streamToColor(std::stringstream& sstream, float* c);
