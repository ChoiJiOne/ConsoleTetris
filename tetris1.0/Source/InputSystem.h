#pragma once

#include "Common.h"

class InputSystem
{
public:
	InputSystem();
	virtual ~InputSystem();

	void Update();
	bool IsCurrKeyPress(const std::string& keyType);
	bool IsPrevKeyPress(const std::string& keyType);

	bool HasKeyType(const std::string& keyType);

private:
	struct KeyState
	{
		int32_t keyCode = 0;
		bool    bIsPressPrevButton = false;
		bool    bIsPressCurrButton = false;
	};

private:
	void UpdateKeyState(KeyState& state);
	bool IsCurrKeyPress(const KeyState& state);
	bool IsPrevKeyPress(const KeyState& state);

private:
	std::unordered_map<std::string, KeyState> keyStateCache;
};