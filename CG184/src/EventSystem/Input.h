#pragma once

#include "../Graphics/Window.h"
#include "../Maths/Vector2D.h"
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
			bool IsKeyPressed(int keyVal); // Temporary
			bool KeyReleased(std::string key);

			bool IsMouseClicked(int button);

			~Input();

            Vector2D static mousePosition;
		private:
			void processInput();
			WindowPtr m_Window;

        };

		
	}
}