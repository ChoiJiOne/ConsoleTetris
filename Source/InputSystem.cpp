#include "InputSystem.h"

InputSystem::InputSystem()
{
	keyStateCache["KeyUp"]     = KeyState{ VK_UP, false, false };
	keyStateCache["KeyDown"]   = KeyState{ VK_DOWN, false, false };
	keyStateCache["KeyLeft"]   = KeyState{ VK_LEFT, false, false };
	keyStateCache["KeyRight"]  = KeyState{ VK_RIGHT, false, false };
	keyStateCache["KeyEscape"] = KeyState{ VK_ESCAPE, false, false };
	keyStateCache["KeySpace"]  = KeyState{ VK_SPACE, false, false };
}

InputSystem::~InputSystem()
{
}

void InputSystem::Update()
{
	for (auto& state : keyStateCache)
	{
		UpdateKeyState(state.second);
	}
}

bool InputSystem::IsCurrKeyPress(const std::string& keyType)
{
	auto keyState = keyStateCache.find(keyType);

	if (keyState == keyStateCache.end())
	{
		return false;
	}
	else
	{
		return IsCurrKeyPress(keyState->second);
	}
}

bool InputSystem::IsPrevKeyPress(const std::string& keyType)
{
	auto keyState = keyStateCache.find(keyType);

	if (keyState == keyStateCache.end())
	{
		return false;
	}
	else
	{
		return IsPrevKeyPress(keyState->second);
	}
}

bool InputSystem::HasKeyType(const std::string& KeyType)
{
	for (auto& State : keyStateCache)
	{
		if (!KeyType.compare(State.first))
		{
			return true;
		}
	}

	return false;
}

void InputSystem::UpdateKeyState(KeyState& state)
{
	state.bIsPressPrevButton = state.bIsPressCurrButton;

	if (GetAsyncKeyState(state.keyCode) & 0x8000) // Press Key
	{
		state.bIsPressCurrButton = true;
	}
	else
	{
		state.bIsPressCurrButton = false;
	}
}

bool InputSystem::IsCurrKeyPress(const KeyState& state)
{
	return state.bIsPressCurrButton;
}

bool InputSystem::IsPrevKeyPress(const KeyState& state)
{
	return state.bIsPressPrevButton;
}

