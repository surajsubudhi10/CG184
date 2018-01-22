#pragma once

#include "../Graphics/Window.h"
#include "../Maths/Vector2D.h"
#include <string>

namespace CG184 
{
	class Scene;
	class Input
	{
	public:
		explicit Input(WindowPtr window, Scene* scene);

		bool KeyPressed(std::string key);
		bool IsKeyPressed(int keyVal); // Temporary
		bool KeyReleased(std::string key);

		bool IsMouseButtonDown(int button);
		bool IsMouseButtonUp(int button);

		void RenderSelection();
		void ProcessSelection();

		~Input();

        Vector2D static mousePosition;
	private:
		void processInput();
		WindowPtr m_Window;
		Scene* m_Scene;

    };
		
}