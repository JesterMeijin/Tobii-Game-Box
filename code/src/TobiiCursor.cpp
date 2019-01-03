#include "TobiiCursor.h"
#include <spdlog/spdlog.h>
#include <tobii/tobii_streams.h>

core::TobiiCursor::TobiiCursor(Window* window, Config* config) :
window(window),
api(nullptr),
device(nullptr),
time_counter_(config->get_int("tobii_reconnect_timer", 2000)),
logger_(nullptr)
{
	logger_ = spdlog::get("root");
	
	tobii_custom_log_t custom_log;
	custom_log.log_context = nullptr;
	custom_log.log_func = [](void* log_context, tobii_log_level_t level, char const* text)
	{
		spdlog::get("root")->trace("Tobii info {} {}", level, text);
	};

	tobii_error_t error = tobii_api_create(&api, nullptr, &custom_log);
	if (error != TOBII_ERROR_NO_ERROR)
	{
		logger_->error("Failed to initialize the Tobii Stream Engine API.\n");
		throw std::exception("Failed to init_device tobii cursor");
	}

	init_device();
}

core::TobiiCursor::~TobiiCursor()
{
	tobii_error_t error;
	if (device != nullptr) {

		logger_->info("Unsubscribing from Tobii gaze stream");
		error = tobii_gaze_point_unsubscribe(device);
		if (error != TOBII_ERROR_NO_ERROR)
			logger_->error("Failed to unsubscribe from wearable data stream.");

		logger_->info("Destroy Tobii device");
		error = tobii_device_destroy(device);
		if (error != TOBII_ERROR_NO_ERROR)
			logger_->error("Failed to destroy device.");
	}

	if (api != nullptr) {
		logger_->info("Destroying the Tobii api");
		error = tobii_api_destroy(api);
		if (error != TOBII_ERROR_NO_ERROR)
			logger_->error("Failed to destroy API.");
	}
}

void core::TobiiCursor::init_device()
{
	std::string device_url = get_device_url();

	logger_->debug("Init device");

	if (!device_url.empty())
	{
		logger_->info("Found device with url : {}", device_url);
		tobii_error_t error = tobii_device_create(api, device_url.c_str(), &device);
		if (error != TOBII_ERROR_NO_ERROR)
		{
			logger_->warn("Can't initialize device");
			device = nullptr;
		}
		else {
			subscribe_device_to_gaze();
		}
	}
}

bool core::TobiiCursor::reconnect_device()
{
	logger_->info("Reconnecting to device");

	tobii_error_t error = tobii_device_reconnect(device);
	
	if (error != TOBII_ERROR_CONNECTION_FAILED) {
		logger_->warn("Reconnection failed: {}", tobii_error_message(error));
		return false;
	}

	return true;
}

std::string core::TobiiCursor::get_device_url()
{
	std::vector<std::string> devices_urls;
	// Enumerate the connected devices, connected devices will be stored in the supplied memory context 
	tobii_error_t error = tobii_enumerate_local_device_urls(api, [](char const* url, void* user_data)
	{
		// The memory context is passed through the user_data void pointer 
		auto context = static_cast<std::vector<std::string>*>(user_data);
		context->push_back(std::string(url));
	}, &devices_urls);

	if (error != TOBII_ERROR_NO_ERROR)
	{
		logger_->error("Failed to list devices {}", tobii_error_message(error));
		return "";
	}
	if (devices_urls.empty())
	{
		logger_->warn("Didn't found any tobii device");
		return "";
	}
	if (devices_urls.size() > 1)
	{
		logger_->warn("Found more than one tobii device (take the first)");
		return devices_urls[0];
	}
	return devices_urls[0];
}

void core::TobiiCursor::subscribe_device_to_gaze()
{
	latest_gaze_data.timestamp_us = 0LL;
	latest_gaze_data.validity = TOBII_VALIDITY_INVALID;

	// Start subscribing to wearable data, in this sample we supply a tobii_wearable_data_t variable to store latest value. 
	tobii_error_t error = tobii_gaze_point_subscribe(
		device, [](tobii_gaze_point_t const* gaze_data, void* user_data)
	{
		// Store the latest wearable data in the supplied storage 
		auto data_storage = static_cast<tobii_gaze_point_t*>(user_data);
		*data_storage = *gaze_data;

		spdlog::get("root")->info("gaze_data {} {} {}",gaze_data->validity, gaze_data->position_xy[0], gaze_data->position_xy[1]);
	}, &latest_gaze_data);

	if (error != TOBII_ERROR_NO_ERROR)
	{
		logger_->error("Failed to subscribe to gaze stream {}", tobii_error_message(error));
		throw std::exception("Error subscribing to gaze stream");
	}
}


bool core::TobiiCursor::get_cursor_position(coord& value)
{

	if(device == nullptr)
	{
		// if we have waited the reconnection time 
		if(time_counter_.isTimePassed())
		{
			time_counter_.reset();
			init_device(); 
		}

		if (device == nullptr) // if the device is still not init
			return false;
	}
	auto error = tobii_device_process_callbacks(device);

	if (error == TOBII_ERROR_CONNECTION_FAILED)
	{
		if (time_counter_.isTimePassed())
		{
			time_counter_.reset();
			// reconnect to the device
			reconnect_device();
		}

		return false;
	}
	else if (error != TOBII_ERROR_NO_ERROR)
	{
		logger_->error("tobii_device_process_callbacks failed: {}", tobii_error_message(error));
		return false;
	}

	if(latest_gaze_data.validity != TOBII_VALIDITY_VALID)
	{
		logger_->warn("Gaze data found but invalid");
		return false;
	}
	
	coord displayResolution = window->get_display_resolution();
	coord offset = window->get_offset_xy();

	value = { 
		static_cast<int>((latest_gaze_data.position_xy[0] * displayResolution.x) - offset.x),
		static_cast<int>((latest_gaze_data.position_xy[1] * displayResolution.y) - offset.y)
	};

	return true;
}

int core::TobiiCursor::getPriority()
{
	return 100;
}