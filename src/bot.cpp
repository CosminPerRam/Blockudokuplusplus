
#include "bot.h"
#include "settings.h"
#include "cellMatrix.h"
#include "game.h"

void Bot::update(sf::RenderWindow& window, sf::Time& dt) {
	elapsedTime += dt;

	if (elapsedTime.asSeconds() > Settings::Gameplay::autoplayDelay) {
		doMove();
		elapsedTime = sf::Time();
	}
}

unsigned Bot::runBranch(std::vector<unsigned> alreadyChosen) {
    return 1;
}

void Bot::doMove() {
    cellMatrix currentMatrix = Game::theTable->getMatrix();

    unsigned scores[3] = { 0 };

    for (unsigned i = 0; i < 3; i++) {
        Block* theCurrentBlock = Game::pickupBoard->pickupableBlocks[i];
        if (theCurrentBlock == nullptr)
            continue;

        std::unique_ptr<std::vector<completetion>> positionCompletetions;
        auto positions = currentMatrix.getBlockPlacingPositions(*theCurrentBlock);
        for (const auto& p : positions) {
            currentMatrix.applyBlock(*theCurrentBlock, p);
            positionCompletetions = currentMatrix.checkCompletetion();
            currentMatrix.executeCompletetions(positionCompletetions, cell::empty);
            scores[i] += positionCompletetions.get()->size();

            /*
            if (firstIndex == -1) {
                if (recursiveCanAnyBlocksBePlaced(i))
                    return true;
            }
            else {
                if (secondIndex == -1)
                    return recursiveCanAnyBlocksBePlaced(firstIndex, i);
                else //this is the third block we process and there ARE possible positions, so, its good
                    return true;
            }*/

            scores[i] -= positionCompletetions.get()->size();
            currentMatrix.executeCompletetions(positionCompletetions, cell::occupied);
            currentMatrix.applyBlock(*theCurrentBlock, p, cell::empty);
        }
    }
}
