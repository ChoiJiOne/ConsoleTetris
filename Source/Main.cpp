#include <iostream>

#include "InputManager.h"
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
			std::cout << "PRESS UP\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::DOWN) == EPressState::PRESSED)
		{
			std::cout << "PRESS DOWN\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::LEFT) == EPressState::PRESSED)
		{
			std::cout << "PRESS LEFT\n";
		}

		if (InputManager::Get().GetKeyPressState(EKeyCode::RIGHT) == EPressState::PRESSED)
		{
			std::cout << "PRESS RIGHT\n";
		}
	}

	return 0;
}