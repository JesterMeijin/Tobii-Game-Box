#ifndef FRAME_INCLUDED
#define FRAME_INCLUDED
#include <SDL/SDL.h>
#include "Window.h"
#include "Button.h"
#include "GameObject.h"
#include "ratio.h"
#include <spdlog/spdlog.h>

namespace core {

	namespace fx {

		/// This template represent a Frame
		/// Any graphical objects (such as Buttons, images...) can be stored in this frame
		/// All the objects stored in this frame with be automatically resized with the window
		template <class T>
		class Frame
		{
		public:

			/// This is the frame constructor that will initialize the frame
			/// The margins parameter indicate margins between the frame and the window on each sides (left, top, right, bottom)
			Frame(Window* window, Config* config, SDL_Rect margins) :
				window_(window),
				config_(config),
				margins_({ margins.x, margins.y, window_->get_width() - margins.w, window_->get_height() - margins.h })
			{
				logger_ = spdlog::get("root");
				previousWindowSize_ = { window_->get_width(), window_->get_height() };
			}

			/// This is the destructor of the frame
			/// It will free all the stored objects
			~Frame()
			{
				for (T* object : objects_)
					core::utils::safe_delete(object);
			}

			/// A function to add template class T objects into the frame
			void add(T* object)
			{
				objects_.push_back(object);
			};

			/// A function to update all objects stored in the frame
			/// It calculate the window resize ratio and apply it onto all objects
			/// Objects will keep their original ratio
			void update(coord cursorPosition)
			{
				resizeRatio_ = { (double)window_->get_width() / (double)previousWindowSize_.x, (double)window_->get_height() / (double)previousWindowSize_.y };
				margins_ = { (int)((double)margins_.x * resizeRatio_.x), (int)((double)margins_.y * resizeRatio_.y), (int)((double)margins_.w * resizeRatio_.x), (int)((double)margins_.h * resizeRatio_.y) };
				previousWindowSize_ = { window_->get_width(), window_->get_height() };

				for (auto object : objects_) {
					object->update(cursorPosition, margins_, resizeRatio_);
				}

			};

			/// This function will return the vector containing the template class T objects
			std::vector<T*> getObjects() 
			{ 
				return objects_; 
			};

			/// This function will return the position and the size of the frame (x, y, w, h)
			SDL_Rect getProperties() 
			{ 
				return margins_; 
			};

			/// This function will return the window resize ratio
			ratio getResizeRatio()
			{
				resizeRatio_ = { (double)window_->get_width() / (double)previousWindowSize_.x, (double)window_->get_height() / (double)previousWindowSize_.y };
				return resizeRatio_;
			}

		protected:
			/// The window to display the object in
			Window* window_;

			/// The configuration of the program
			Config* config_;

			/// The logger
			std::shared_ptr<spdlog::logger> logger_;

			/// The last saved window size before resize
			coord previousWindowSize_;

			/// The window resize ratio
			ratio resizeRatio_;

			/// The position and size of the frame
			SDL_Rect margins_;
			
			/// The vector containing all the template class T objects
			std::vector<T*> objects_;
		};
	}
	
}

#endif
