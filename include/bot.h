
#pragma once

#include "impl.h"

class Bot : Updater
{
private:
	sf::Time elapsedTime;

	unsigned runBranch(std::vector<unsigned> alreadyChosen);

public:
	void update(sf::RenderWindow& window, sf::Time& dt);

	void doMove();
};