#include "Case.h"
#include "../../Constants.h"

game::rb::Case::Case(int index, core::Window* window, core::MusicManager* musicManager, int x, int y, int triggerTime):
Button(window, musicManager, triggerTime, " ", 32, BLACK_COLOR, "ressources/games/remember/NumberSprites.png", {x, y, 100, 100}),
index_(index)
{
	SDL_Rect cropRect = { 0, 3 * 250, 250, 250 };
	setCropRect(cropRect);
	setSound("ressources/games/remember/casePressed.ogg");
}

int game::rb::Case::getIndex()
{
	return index_;
}
