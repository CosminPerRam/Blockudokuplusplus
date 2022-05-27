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
 - [SFML](https://www.sfml-dev.org/) 2.5.1! (Using all modules except for the `network` one)
 - [imgui](https://github.com/ocornut/imgui) 1.87
 - [imgui-sfml](https://github.com/eliasdaler/imgui-sfml) 2.5

## Building the game
### Windows - Visual Studio
1. Clone/download the repo
2. Enter the repo directory
3. Create a folder named `libraries`
4. Download `SFML 2.5.1 32-bit VS 2017` (from [here](https://www.sfml-dev.org/download/sfml/2.5.1/))
5. Unzip and place the contents in the `libraries` folder. 
(Ex: the path for the `bin` folder inside SFML should look like this: `repo/libraries/SFML-2.5.1/bin`)
6. Create a folder named `imgui` inside `libraries`
7. Download `imgui` (from [here](https://github.com/ocornut/imgui)), unzip it and extract all .cpp and .h files into the `imgui` folder
8. Download `imgui-sfml` (from [here](https://github.com/eliasdaler/imgui-sfml)), unzip it and extract all .cpp and .h files into the `imgui` folder
9. Inside `imconfig.h` add `#include "imconfig-SFML.h"` at the top of the file  
([this video](https://www.youtube.com/watch?v=2YS5WJTeKpI) is a good tutorial for doing the last 3 steps)
10. Open `Blockudoku.sln`
11. Select the desired configuration (`Debug`/`Release`) and build!  
*. Note: `openal32.dll` (from SFML's `bin` folder) is needed to be in the Debug/Release folder.

### Linux/MacOS - CMake
*. You still need to do the steps `3, 7, 8, 9` from above.  
Clone the repo and check out the cmake script. (Thanks [@ChrisTrasher](https://github.com/ChrisThrasher))
