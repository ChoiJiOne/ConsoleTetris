#include <InputManager.h>

#include <array>
#include <windows.h>

std::array<EKeyCode, 8> KeyCodes = {
	EKeyCode::TAB,
	EKeyCode::ENTER,
	EKeyCode::ESCAPE,
	EKeyCode::SPACE,
	EKeyCode::LEFT,
	EKeyCode::UP,
	EKeyCode::RIGHT,
	EKeyCode::DOWN
};

InputManager::InputManager()
{
	for (const auto& KeyCode : KeyCodes)
	{
		PrevKeyState_[KeyCode] = false;
		CurrKeyState_[KeyCode] = false;
	}
}

void InputManager::Tick()
{
	PrevKeyState_ = CurrKeyState_;

	for (const auto& KeyCode : KeyCodes)
	{
		CurrKeyState_[KeyCode] = IsPressKey(KeyCode);
	}
}

EPressState InputManager::GetKeyPressState(const EKeyCode& InKeyCode) const
{
	EPressState PressState = EPressState::NONE;

	if (PrevKeyState_.at(InKeyCode))
	{
		if (CurrKeyState_.at(InKeyCode))
		{
			PressState = EPressState::HELD;
		}
		else
		{
			PressState = EPressState::RELEASED;
		}
	}
	else
	{
		if (CurrKeyState_.at(InKeyCode))
		{
			PressState = EPressState::PRESSED;
		}
		else
		{
			PressState = EPressState::NONE;
		}
	}

	return PressState;
}

bool InputManager::IsPressKey(const EKeyCode& InKeyCode) const
{
	return (GetAsyncKeyState(static_cast<int32_t>(InKeyCode)) & 0x8000);
}
