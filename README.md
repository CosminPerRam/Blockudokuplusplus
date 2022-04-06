# Blockudoku++
This game is a copy of the Blockudoku mobile game ([Android](https://play.google.com/store/apps/details?id=com.easybrain.block.puzzle.games&hl=en&gl=US), [IOS](https://apps.apple.com/us/app/blockudoku-block-puzzle-game/id1452227871)) written in C++14 using SFML, originally made as the final project for the university's OOP class.  
See a video comparison between the original game and this one [here](https://youtu.be/3Z-Xvgebu6Y).

## Resources
The game uses audio effects from the original Blockudoku game.  
It also uses icons from [Icons8](https://icons8.com/).

## Precompiled binaries
Check the [releases](https://github.com/CosminPerRam/Blockudokuplusplus/releases) page.
Although I can provide binaries only for Windows (and sometimes for Apple Silicon), the code is cross platform!

## Dependencies
Only [SFML](https://www.sfml-dev.org/) 2.5.1! (Using all modules except for the `network` one)

## Building the game
### Windows - Visual Studio
1. Clone/download the repo
2. Enter the repo directory
3. Create a folder named `libraries`
4. Download `SFML 2.5.1 32-bit VS 2017` (from [here](https://www.sfml-dev.org/download/sfml/2.5.1/))
5. Unzip and place the contents in the `libraries` folder.  
(Ex: the path for the `bin` folder inside SFML should look like this: `repo/libraries/SFML-2.5.1/bin`)
6. Open `Blockudoku.sln` (originally made with Visual Studio 2019)
7. Select the desired configuration (`Debug`/`Release`) and build!
*. Note: `openal32.dll` (from SFML's `bin` folder) is needed to be in the Debug/Release folder.

### Linux/MacOS - CMake
Clone the repo and check out the cmake script. (Thanks [@ChrisTrasher](https://github.com/ChrisThrasher))
