#pragma once

#include "../Graphics/Window.h"
#include <string>

namespace CG184 
{
	namespace Eventsystem 
	{
		class Input
		{
		public:
			explicit Input(WindowPtr window);

			bool KeyPressed(std::string key);
			bool KeyPressed(int keyVal); // Temporary
			bool KeyReleased(std::string key);

			bool MouseClicked(std::string key);

			~Input();

		private:
			void processInput();


			WindowPtr m_Window;
		};

		
	}
}