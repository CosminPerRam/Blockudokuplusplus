
#pragma once

/*
	Defines every element where it will draw
	some components are depended on other component's location,
	this simplifies modifying the ui element's positions.
*/

#define WINDOW_HEIGHT 340
#define WINDOW_WIDTH 470

#define CELL_SPACING 32

#define TABLE_SIZE 9
#define TABLE_POSITION_X 25
#define TABLE_POSITION_Y 25

#define PICKUP_POSITION_X 10 * CELL_SPACING + TABLE_POSITION_X
#define PICKUP_POSITION_Y TABLE_POSITION_Y

#define PICKUP_SCALE 0.8f
#define PICKUP_OFFSET CELL_SPACING / 2 * PICKUP_SCALE

#define SCORE_POSITION_X TABLE_POSITION_X
#define SCORE_POSITION_Y 5

#define SCORE_POSITION2_X TABLE_POSITION_X
#define SCORE_POSITION2_Y 10 * CELL_SPACING - 12

#define SCORE_POPULAR_PIECE_POSITION_Y 197
#define SCORE_POPULAR_PIECE_POSITION_X 278

#define RESTART_POSITION_X WINDOW_HEIGHT / 2
#define RESTART_POSITION_Y 400
#define RESTART_SIZE_WIDTH 200
#define RESTART_SIZE_HEIGHT 50

#define AUDIO_POSITION_X 285
#define AUDIO_POSITION_Y 0
