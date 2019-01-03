# Projet eye tracking

## Running game
To run the program, you can either compile it or go in release folder.
You can run ``TobiiGamebox.exe`` in the release folder to run the last release of the game.

## Installation

### Users
To make the sotware running as expected, please download and install the following requirements before : 
- [Microsoft Visual C++ Redistributable for Visual Studio 2017](https://support.microsoft.com/en-ph/help/2977003/the-latest-supported-visual-c-downloads)
- [Logiciel Tobii Gaming (Eye Tracking Core Software)](https://tobiigaming.com/getstarted/)

Once installed, you can run the ``TobiiGamebox.exe`` software from the ``release`` folder. Enjoy !

### Developpers

The project was made with Visual Studio 2017. The project files are available in the ``code`` directory.
You can also import the project with cmake with your favorite IDE.

Sources are availables in ``code/src``
The libs and includes used for this project are located in ``code/lib`` and ``code/include``
The ``code/ressources`` contains all the programs assets.

## Dependancies
- [SDL v2](https://www.libsdl.org/index.php) - For graphics and user's events 
- SDL dependancies
	- [SDL Image](https://www.libsdl.org/projects/SDL_image/) - For easier assets loading 
	- [SDL TTF](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html) - For Text rendering 
	- [SDL Mixer](https://www.libsdl.org/projects/SDL_mixer/) - For Music loading 
- [Tobii Stream Engine](https://developer.tobii.com/consumer-eye-trackers/stream-engine/) - For the Tobii integration 
- [SPDLOG](https://github.com/gabime/spdlog) - For logging features 


## Specifications
https://1drv.ms/w/s!AsDymYKk3_9Ji3R0CMLmionB1o76

## Drive 
https://drive.google.com/drive/folders/1hBmVfWo0LXkW_xOAVqUmnGTyNfuHgufS?usp=sharing