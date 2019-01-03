#ifndef GAZE_OBJECT_INCLUDED
#define GAZE_OBJECT_INCLUDED
#include "GameObject.h"

namespace core {

	/// This is a specific game object
	/// It goal is to display the position of the cursor on the screen
	/// This position is called The Gaze
	class GazeObject : public GameObject
	{
	public:
		GazeObject(Window* window);
		~GazeObject();

		void update(coord gazePosition) override;
	};
}

#endif