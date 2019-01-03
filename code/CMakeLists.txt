cmake_minimum_required(VERSION 3.12)
project(code)

set(CMAKE_CXX_STANDARD 14)
#set ( CMAKE_CXX_FLAGS "-m64")

include_directories(include)
link_directories(lib)

add_executable(code
        src/game/remember/Case.cpp
        src/game/remember/Case.h
        src/game/remember/RememberGame.cpp
        src/game/remember/RememberGame.h
        src/Application.cpp
        src/Application.h
        src/Button.cpp
        src/Button.h
        src/Config.cpp
        src/Config.h
        src/Constants.h
        src/coord.h
        src/Cursor.cpp
        src/Cursor.h
        src/CursorMovementManager.cpp
        src/CursorMovementManager.h
        src/Frame.h
        src/FrameCounter.cpp
        src/FrameCounter.h
        src/Game.cpp
        src/Game.h
        src/GameObject.cpp
        src/GameObject.h
        src/GazeObject.cpp
        src/GazeObject.h
        src/InputDefinition.h
        src/InputManager.cpp
        src/InputManager.h
        src/Label.cpp
        src/Label.h
        src/Leaderboard.cpp
        src/Leaderboard.h
        src/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/MouseCursor.cpp
        src/MouseCursor.h
        src/ratio.h
        src/Statistics.cpp
        src/Statistics.h
        src/SubMenu.cpp
        src/SubMenu.h
        src/TimeCounter.cpp
        src/TimeCounter.h
        src/TobiiCursor.cpp
        src/TobiiCursor.h
        src/UncopyableObject.h
        src/Utils.cpp
        src/Utils.h
        src/Window.cpp
        src/Window.h
        src/StatisticsManager.cpp
        src/StatisticsManager.h
        src/MusicManager.cpp
        src/MusicManager.h
        src/Settings.cpp
        src/Settings.h)

target_link_libraries(code SDL2 SDL2main SDL2_ttf SDL2_mixer SDL2_image tobii_stream_engine)