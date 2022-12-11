#include <iostream>

#include "InputManager.h"
#include "ConsoleManager.h"
#include "Vector.hpp"

int main(void)
{
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
			ConsoleManager::Get().MoveCursor(Vec2i(10, 0));
			ConsoleManager::Get().SetTextColor(EColor::AQUA);
			std::cout << "PRESS UP\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
		{
			ConsoleManager::Get().MoveCursor(Vec2i(10, 20));
			ConsoleManager::Get().SetTextColor(EColor::WHITE);
			std::cout << "PRESS DOWN\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().MoveCursor(Vec2i(0, 10));
			ConsoleManager::Get().SetTextColor(EColor::GRAY);
			std::cout << "PRESS LEFT\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::RIGHT) == EPressState::PRESSED)
		{
			ConsoleManager::Get().MoveCursor(Vec2i(20, 10));
			ConsoleManager::Get().SetTextColor(EColor::GREEN);
			std::cout << "PRESS RIGHT\n";
		}
	}

	return 0;
}