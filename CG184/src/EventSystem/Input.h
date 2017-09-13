#pragma once

#include "../Graphics/Window.h"
#include <string>

namespace CG184 
{
	namespace eventsystem 
	{
		class Input
		{
		public:
			Input(Window* window);

			bool KeyPressed(std::string key);
			bool KeyPressed(int keyVal); // Temporary
			bool KeyReleased(std::string key);

			bool MouseClicked(std::string key);

			~Input();

		private:
			void processInput();


			Window* win;
		};

		
	}
}