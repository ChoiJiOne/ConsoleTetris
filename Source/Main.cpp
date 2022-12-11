#include <iostream>

#include "Debug.h"
#include "InputManager.h"
#include "ConsoleManager.h"
#include "Vector.hpp"

int main(void)
{
	SetUnhandledExceptionFilter(UnhandledExceptionHandler);

	bool bIsDone = false;
	while (!bIsDone)
	{
		InputManager::Get().Tick();

		if (InputManager::Get().GetKeyPressState(EKeyCode::ESCAPE) == EPressState::PRESSED)
		{
			bIsDone = true;
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::UP) == EPressState::PRESSED)
		{
			ConsoleManager::Get().RenderText(Vec2i(10, 0), "PRESS UP", EColor::AQUA);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
		{
			ConsoleManager::Get().RenderText(Vec2i(10, 20), "PRESS DOWN", EColor::WHITE);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().RenderText(Vec2i(0, 10), "PRESS LEFT", EColor::GRAY);
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::RIGHT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().RenderText(Vec2i(20, 10), "PRESS RIGHT", EColor::GREEN);
		}
	}

	return 0;
}