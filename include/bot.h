
#pragma once

#include "impl.h"

class Bot : Updater
{
private:
	sf::Time elapsedTime;

	struct Branch
	{
		enum class Type { Single, Double, Triple };

		Type type = Type::Single;
		unsigned firstIndex = 0, secondIndex = 0, thirdIndex = 0;
		sf::Vector2u firstPosition = {0, 0}, secondPosition = { 0, 0 }, thirdPosition = { 0, 0 };

		Branch(unsigned firstIndex, sf::Vector2u firstPosition);
		Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition);
		Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition, unsigned thirdIndex, sf::Vector2u thirdPosition);
	};

	unsigned evaluateBranch(const Branch& branch);

public:
	void update(sf::RenderWindow& window, sf::Time& dt);

	void doMove();
};