# Blockudoku++
This is a very basic copy of the Blockudoku mobile game ([Android](https://play.google.com/store/apps/details?id=com.easybrain.block.puzzle.games&hl=en&gl=US), [IOS](https://apps.apple.com/us/app/blockudoku-block-puzzle-game/id1452227871)) written in C++14 using SFML, originally made as the final project for the university's OOP class.

## Precompiled binaries
Check the [releases](https://github.com/CosminPerRam/Blockudokuplusplus/releases) page.  
Although precompiled binaries are only available for Windows, the code is cross platform.

## Dependencies
Only [SFML](https://www.sfml-dev.org/) 2.5.1!  
Using all modules except for the network one.

## Building the game
1. Clone/download the repo
2. Enter the repo directory
3. Create a folder named `libraries`
4. Download SFML 2.5.1 32-bit VS 2017 (from [here](https://www.sfml-dev.org/download/sfml/2.5.1/))
5. Unzip and place the contents in the `libraries` folder.  
(Ex: the path for the `bin` folder inside SFML should look like this: `repo/libraries/SFML-2.5.1/bin`)
6. (Windows) Open `Blockudoku.sln` (originally made with Visual Studio 2019)
7. (Windows) Select the desired configuration (Debug/Release) and build!
