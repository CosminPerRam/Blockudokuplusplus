
#pragma once

#include <array>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "block.h"
#include "spacing.h"
#include "table.h"
#include "score.h"

enum class pickupBlocks { all = 0, missing, existing };

/*
	Manages picking up, regenerating the blocks and checking if the game is lost.
	The rest of the classes have nothing to do with its components.
*/
class PickupBoard
{
private:
	sf::Color MARGINS;
	sf::CircleShape mouseCircle;

	sf::VertexArray borders = sf::VertexArray(sf::Lines, 2 * 2 + 4 * 2);

	std::array<Block*, 3> pickupableBlocks = { nullptr };

	int pickedUpIndex = -1;
	sf::Vector2f pickedUpPosition;
	sf::Vector2i pickedUpPreviewCoords;
	sf::Vector2i paintModePreviewCoords;

	static Block paintModeBlock; //quite the hacky move to avoid refactoring a lot of code just to preview the mouse position...

	const sf::Vector2f startPosition = { PICKUP_POSITION_X, PICKUP_POSITION_Y };
	const int BoardLength = CELL_SPACING * 9, BoardHeight = CELL_SPACING * 3;

	void regenerateBlocks(pickupBlocks type);
	void placeIndexInDefaultPosition(unsigned i);

	bool anyBlocksLeft();
	bool canAnyBlocksBePlaced();
	bool recursiveCanAllBlocksBePlaced(int firstIndex = -1, int secondIndex = -1);

	void updateBlocksState();

	void calculateVertexes();

public:
	PickupBoard();
	~PickupBoard();

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	void update(sf::RenderWindow& window, sf::Time& dt);

	void updateColors();

	bool isBoardLost();

	void reset();

	friend class ImguiInterface;
	friend class Bot;

	friend struct Settings::Gameplay;
};
