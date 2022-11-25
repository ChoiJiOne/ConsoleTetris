#include "InputManager.h"

#include <array>
#include <ncurses.h>

InputManager InputManager::InputManager_;

static std::array<EKeyCode, 7> KeyCodes = {
    EKeyCode::ENTER,
    EKeyCode::ESC,
    EKeyCode::SPACE,
    EKeyCode::DOWN,
    EKeyCode::UP,
    EKeyCode::LEFT,
    EKeyCode::RIGHT
};

InputManager::InputManager()
{
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    PrevKeyState_.insert({EKeyCode::ENTER, false});
    PrevKeyState_.insert({EKeyCode::ESC,   false});
    PrevKeyState_.insert({EKeyCode::SPACE, false});
    PrevKeyState_.insert({EKeyCode::UP,    false});
    PrevKeyState_.insert({EKeyCode::LEFT,  false});
    PrevKeyState_.insert({EKeyCode::RIGHT, false});
    
    CurrKeyState_.insert({EKeyCode::ENTER, false});
    CurrKeyState_.insert({EKeyCode::ESC,   false});
    CurrKeyState_.insert({EKeyCode::SPACE, false});
    CurrKeyState_.insert({EKeyCode::UP,    false});
    CurrKeyState_.insert({EKeyCode::LEFT,  false});
    CurrKeyState_.insert({EKeyCode::RIGHT, false});
}

InputManager::~InputManager()
{
}

void InputManager::Tick()
{
    for(const auto& KeyCode : KeyCodes)
    {
        PrevKeyState_[KeyCode] = CurrKeyState_[KeyCode];
    }

    for(const auto& KeyCode : KeyCodes)
    {
        CurrKeyState_[KeyCode] = false;
    }

    if(IsDetectPressKeyboard())
    {
        EKeyCode KeyCode = static_cast<EKeyCode>(getch());
        CurrKeyState_[KeyCode] = true;
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

bool InputManager::IsDetectPressKeyboard()
{
    bool bIsDetect = false;
    int32_t CurrentKey = getch();

    if (CurrentKey != ERR) 
    {   
        for(const auto& KeyCode : KeyCodes)
        {
            if(static_cast<int32_t>(KeyCode) == CurrentKey)
            {
                bIsDetect = true;
                ungetch(CurrentKey);
            }
        }
    }

    return bIsDetect;
}