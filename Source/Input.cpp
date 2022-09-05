#include "Input.h"

static Input::EKeyType KeyTypes[] = {
	Input::EKeyType::Up,
	Input::EKeyType::Down,
	Input::EKeyType::Left,
	Input::EKeyType::Right,
	Input::EKeyType::Escape,
	Input::EKeyType::Space,
	Input::EKeyType::Enter,
};

Input::Input()
{
	for (const auto& KeyType : KeyTypes)
	{
		PrevKeyState_[KeyType] = false;
		CurrKeyState_[KeyType] = false;
	}
}

Input::Input(Input&& InInstance) noexcept
	: PrevKeyState_(InInstance.PrevKeyState_)
	, CurrKeyState_(InInstance.CurrKeyState_)
{
}

Input::Input(const Input& InInstance) noexcept
	: PrevKeyState_(InInstance.PrevKeyState_)
	, CurrKeyState_(InInstance.CurrKeyState_)
{
}

Input::~Input()
{
}

Input& Input::operator=(Input&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	PrevKeyState_ = InInstance.PrevKeyState_;
	CurrKeyState_ = InInstance.CurrKeyState_;

	return *this;
}

Input& Input::operator=(const Input& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	PrevKeyState_ = InInstance.PrevKeyState_;
	CurrKeyState_ = InInstance.CurrKeyState_;

	return *this;
}

void Input::Update()
{
	PrevKeyState_ = CurrKeyState_;

	for (const auto& KeyType : KeyTypes)
	{
		CurrKeyState_[KeyType] = IsPressKey(KeyType);
	}
}

Input::EPressState Input::GetKeyPressState(const EKeyType& InKeyType) const
{
	EPressState PressState = EPressState::None;

	if (PrevKeyState_.at(InKeyType))
	{
		if (CurrKeyState_.at(InKeyType))
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
		if (CurrKeyState_.at(InKeyType))
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

bool Input::IsPressKey(const EKeyType& InKeyType) const
{
	return (GetAsyncKeyState(static_cast<int32_t>(InKeyType)) & 0x8000);
}
