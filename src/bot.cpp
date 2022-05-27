
#include "bot.h"
#include "settings.h"
#include "cellMatrix.h"
#include "game.h"

#include <array>

void Bot::update(sf::RenderWindow& window, sf::Time& dt) {
	elapsedTime += dt;

	if (elapsedTime.asSeconds() > Settings::Gameplay::autoplayDelay) {
		Bot::doMove();

		elapsedTime = sf::Time();
	}
}

Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), type(Type::Single) { }
Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), secondIndex(secondIndex), secondPosition(secondPosition), type(Type::Double) { }
Bot::Branch::Branch(unsigned firstIndex, sf::Vector2u firstPosition, unsigned secondIndex, sf::Vector2u secondPosition, unsigned thirdIndex, sf::Vector2u thirdPosition)
    : firstIndex(firstIndex), firstPosition(firstPosition), secondIndex(secondIndex), secondPosition(secondPosition), thirdIndex(thirdIndex), thirdPosition(thirdPosition), type(Type::Triple) { }

unsigned Bot::evaluateBranch(const Branch& branch) {
    cellMatrix theMatrix = Game::theTable->theMatrix;

    Block* firstBlock = Game::pickupBoard->pickupableBlocks[branch.firstIndex];
    theMatrix.applyBlock(*firstBlock, branch.firstPosition);
    auto firstCompletions = theMatrix.checkCompletetion();
    theMatrix.executeCompletetions(firstCompletions, cell::empty);

    if (branch.type != Branch::Type::Single) {
        Block* secondBlock = Game::pickupBoard->pickupableBlocks[branch.secondIndex];

        theMatrix.applyBlock(*secondBlock, branch.secondPosition);
        auto secondCompletions = theMatrix.checkCompletetion();
        theMatrix.executeCompletetions(secondCompletions, cell::empty);

        if (branch.type != Branch::Type::Double) {
            Block* thirdBlock = Game::pickupBoard->pickupableBlocks[branch.thirdIndex];
            
            theMatrix.applyBlock(*thirdBlock, branch.thirdPosition);
            auto thirdCompletions = theMatrix.checkCompletetion();
            theMatrix.executeCompletetions(thirdCompletions, cell::empty);
        }
    }

    return theMatrix.getEmptyCellsAmount();
}

void Bot::doMove() {
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
            if (missingBlocks == 2)
            {
                branches.emplace_back(firstIndex, firstPosition);
                continue;
            }
            //add block checks

            for (unsigned secondIndex = 0; secondIndex < 3; secondIndex++) {
                Block* secondBlock = Game::pickupBoard->pickupableBlocks[secondIndex];
                if (secondBlock == nullptr || secondIndex == firstIndex)
                    continue;

                auto secondPositions = currentMatrix.getBlockPlacingPositions(*secondBlock);
                for (const auto& secondPosition : secondPositions)
                {
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
                }
            }
        }
    }

    std::vector<unsigned> scores(branches.size());
    for (unsigned i = 0; i < branches.size(); i++)
        scores[i] = evaluateBranch(branches[i]);

    if (branches.size() == 0)
        return;

    //executing the best branch...
    unsigned highestScoreIndex = std::distance(scores.begin(), std::max_element(scores.begin(), scores.end()));
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
