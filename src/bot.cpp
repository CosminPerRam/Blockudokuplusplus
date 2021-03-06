
#include <array>

#include "bot.h"
#include "settings.h"
#include "cellMatrix.h"
#include "game.h"

void Bot::update(sf::RenderWindow& window, sf::Time& dt) {
    if (Game::theScore->isGameLost())
        return;

	if (dt.asSeconds() - elapsedTime.asSeconds() > Settings::Gameplay::autoplayDelay) {
		Bot::doSet();

        elapsedTime = dt;
	}
}

Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), type(Type::Single), score(Game::theTable->theMatrix.getEmptyCellsAmount()) { }
Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), secondIndex(secondIndex), secondPosition(secondPosition), type(Type::Double), score(Game::theTable->theMatrix.getEmptyCellsAmount()) { }
Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition, unsigned thirdIndex, sf::Vector2u thirdPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), secondIndex(secondIndex), secondPosition(secondPosition), thirdIndex(thirdIndex), thirdPosition(thirdPosition), type(Type::Triple), score(Game::theTable->theMatrix.getEmptyCellsAmount()) { }

void Bot::doSet() {
    cellMatrix currentMatrix = Game::theTable->getMatrix();

    unsigned missingBlocks = 0;

    for (unsigned i = 0; i < 3; i++) {
        if (Game::pickupBoard->pickupableBlocks[i] == nullptr)
            missingBlocks++;
    }

    std::vector<Branch> branches;

    for (unsigned firstIndex = 0; firstIndex < 3; firstIndex++) {
        Block* firstBlock = Game::pickupBoard->pickupableBlocks[firstIndex];
        if (firstBlock == nullptr)
            continue;

        auto firstPositions = currentMatrix.getBlockPlacingPositions(*firstBlock);
        for (const auto& firstPosition : firstPositions)
        {
            currentMatrix.applyBlock(*firstBlock, firstPosition);
            auto firstCompletions = currentMatrix.checkCompletetion();
            currentMatrix.executeCompletetions(firstCompletions, cell::empty);

            if (missingBlocks == 2)
            {
                branches.emplace_back(firstIndex, firstPosition);
                continue;
            }

            for (unsigned secondIndex = 0; secondIndex < 3; secondIndex++) {
                Block* secondBlock = Game::pickupBoard->pickupableBlocks[secondIndex];
                if (secondBlock == nullptr || secondIndex == firstIndex)
                    continue;

                auto secondPositions = currentMatrix.getBlockPlacingPositions(*secondBlock);
                for (const auto& secondPosition : secondPositions)
                {
                    currentMatrix.applyBlock(*secondBlock, secondPosition);
                    auto secondCompletions = currentMatrix.checkCompletetion();
                    currentMatrix.executeCompletetions(secondCompletions, cell::empty);

                    if (missingBlocks == 1)
                    {
                        branches.emplace_back(firstIndex, firstPosition, secondIndex, secondPosition);
                        continue;
                    }

                    for (unsigned thirdIndex = 0; thirdIndex < 3; thirdIndex++) {
                        Block* thirdBlock = Game::pickupBoard->pickupableBlocks[thirdIndex];
                        if (thirdBlock == nullptr || thirdIndex == firstIndex || thirdIndex == secondIndex)
                            continue;

                        auto thirdPosition = currentMatrix.getBlockPlacingPositions(*thirdBlock);
                        for (const auto& thirdPosition : thirdPosition)
                            branches.emplace_back(firstIndex, firstPosition, secondIndex, secondPosition, thirdIndex, thirdPosition);
                    }

                    currentMatrix.executeCompletetions(secondCompletions, cell::occupied);
                    currentMatrix.applyBlock(*secondBlock, secondPosition, cell::empty);
                }
            }

            currentMatrix.executeCompletetions(firstCompletions, cell::occupied);
            currentMatrix.applyBlock(*firstBlock, firstPosition, cell::empty);
        }
    }

    if (branches.size() == 0) {
        Settings::Gameplay::autoplay = false;
        return;
    }

    unsigned highestScoreAmount = 0, highestScoreIndex = 0;
    for (unsigned i = 0; i < branches.size(); i++) {
        const Branch& b = branches[i];
        if (b.score > highestScoreAmount) {
            highestScoreAmount = b.score;
            highestScoreIndex = i;
        }
    }

    //executing the best branch...
    const Branch& highestScoreBranch = branches[highestScoreIndex];

    Block*& firstBlock = Game::pickupBoard->pickupableBlocks[highestScoreBranch.firstIndex];
    Game::theTable->applyBlock(*firstBlock, highestScoreBranch.firstPosition);

    delete firstBlock; firstBlock = nullptr;

    if (missingBlocks < 2) {
        Block*& secondBlock = Game::pickupBoard->pickupableBlocks[highestScoreBranch.secondIndex];
        Game::theTable->applyBlock(*secondBlock, highestScoreBranch.secondPosition);

        delete secondBlock; secondBlock = nullptr;

        if (missingBlocks < 1) {
            Block*& thirdBlock = Game::pickupBoard->pickupableBlocks[highestScoreBranch.thirdIndex];
            Game::theTable->applyBlock(*thirdBlock, highestScoreBranch.thirdPosition);

            delete thirdBlock; thirdBlock = nullptr;
        }
    }

    Game::pickupBoard->updateBlocksState();
}
