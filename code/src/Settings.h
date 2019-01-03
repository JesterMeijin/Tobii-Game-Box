#ifndef SETTINGS_INCLUDED
#define SETTINGS_INCLUDED

#include "SubMenu.h"

namespace core {

    /// The settings sub menu
    class Settings : public SubMenu
    {
    public:
        /// Build the settings menu with all the required compnents
        Settings(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config);
        ~Settings();

        /// Display the settings
        void display(Game* game) override;
    };
}

#endif //SETTINGS_INCLUDED
