#include "Input.h"

static Input::EKeyType KeyTypes[] = {
	Input::EKeyType::Up,
	Input::EKeyType::Down,
	Input::EKeyType::Left,
	Input::EKeyType::Right,
	Input::EKeyType::Escape,
	Input::EKeyType::Space
};

Input::Input()
{
	for (const auto& KeyType : KeyTypes)
	{
		PrevKeyState[KeyType] = false;
		CurrKeyState[KeyType] = false;
	}
}

Input::Input(Input&& InInstance) noexcept
	: PrevKeyState(InInstance.PrevKeyState)
	, CurrKeyState(InInstance.CurrKeyState)
{
}

Input::Input(const Input& InInstance) noexcept
	: PrevKeyState(InInstance.PrevKeyState)
	, CurrKeyState(InInstance.CurrKeyState)
{
}

Input::~Input()
{
}

Input& Input::operator=(Input&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	PrevKeyState = InInstance.PrevKeyState;
	CurrKeyState = InInstance.CurrKeyState;

	return *this;
}

Input& Input::operator=(const Input& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	PrevKeyState = InInstance.PrevKeyState;
	CurrKeyState = InInstance.CurrKeyState;

	return *this;
}

void Input::Update()
{
	PrevKeyState = CurrKeyState;

	for (const auto& KeyType : KeyTypes)
	{
		CurrKeyState[KeyType] = IsPressKey(KeyType);
	}
}

Input::EPressState Input::GetKeyPressState(const EKeyType& InKeyType)
{
	EPressState PressState = EPressState::None;

	if (PrevKeyState[InKeyType])
	{
		if (CurrKeyState[InKeyType])
		{
			PressState = EPressState::Held;
		}
		else
		{
			PressState = EPressState::Released;
		}
	}
	else
	{
		if (CurrKeyState[InKeyType])
		{
			PressState = EPressState::Pressed;
		}
		else
		{
			PressState = EPressState::None;
		}
	}

	return PressState;
}

bool Input::IsPressKey(const EKeyType& InKeyType)
{
	return (GetAsyncKeyState(static_cast<int32_t>(InKeyType)) & 0x8000);
}
