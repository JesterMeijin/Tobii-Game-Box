#ifndef TOBII_CURSOR_INCLUDED
#define TOBII_CURSOR_INCLUDED

#include "Cursor.h"

#include <tobii/tobii.h>
#include <spdlog/logger.h>
#include <tobii/tobii_streams.h>
#include "Window.h"
#include "TimeCounter.h"

namespace  core {

	/// This class represent a cursor using the Tobii API
	class TobiiCursor : public Cursor
	{
	public:
		/// Build the tobii cursor by initializing the tobii api and by trying to connect to the plugged device
		TobiiCursor(Window* window, Config* config);
		~TobiiCursor();

		/// See Cursor
		bool get_cursor_position(coord& value) override;

		/// See Cursor
		int getPriority() override;

	private:

		/// Initialize the tobii device with the Tobii api
		void init_device();

		/// Find the url to communicate with the Tobii device
		std::string get_device_url();

		/// Subscribe to gaze (cursor position) events from the Tobii API
		void subscribe_device_to_gaze();

		/// Reconnect to the device in case it has been deconected form the computer
		bool reconnect_device();

		/// The window to hava access to the resolution and position
		Window* window;

		/// Tobii SDK related

		/// This is the api used by all the call to the Tobii sdk
		tobii_api_t* api;

		/// This is the Tobii object representing the device
		tobii_device_t* device;

		/// This is the last position recorded for the Tobii cursor position
		tobii_gaze_point_t latest_gaze_data;

		/// This is the time counter used to check the reconnection time
		TimeCounter time_counter_;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;
	};
}

#endif // TOBII_CURSOR_INCLUDED
