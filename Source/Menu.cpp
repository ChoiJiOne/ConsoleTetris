#include "Macro.h"
#include "Input.h"
#include "Menu.h"

Menu::Menu(
	const std::vector<std::string>& InElements, 
	const Console::ETextColor& InSelectColor, 
	const Console::ETextColor& InNormalColor
): Elements_(InElements),
   SelectColor_(InSelectColor), 
   NormalColor_(InNormalColor), 
   CurrentSelectElement_(0)
{
	CHECK((Elements_.size() > 0), "number of menu is 0");
}

Menu::Menu(Menu&& InInstance) noexcept
	: Elements_(InInstance.Elements_)
	, CurrentSelectElement_(InInstance.CurrentSelectElement_)
	, SelectColor_(InInstance.SelectColor_)
	, NormalColor_(InInstance.NormalColor_)
	, bIsSwitch_(InInstance.bIsSwitch_)
{
}

Menu::Menu(const Menu& InInstance) noexcept
	: Elements_(InInstance.Elements_)
	, CurrentSelectElement_(InInstance.CurrentSelectElement_)
	, SelectColor_(InInstance.SelectColor_)
	, NormalColor_(InInstance.NormalColor_)
	, bIsSwitch_(InInstance.bIsSwitch_)
{
}

Menu::~Menu()
{
}

Menu& Menu::operator=(Menu&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Elements_ = InInstance.Elements_;
	CurrentSelectElement_ = InInstance.CurrentSelectElement_;
	SelectColor_ = InInstance.SelectColor_;
	NormalColor_ = InInstance.NormalColor_;
	bIsSwitch_ = InInstance.bIsSwitch_;

	return *this;
}

Menu& Menu::operator=(const Menu& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Elements_ = InInstance.Elements_;
	CurrentSelectElement_ = InInstance.CurrentSelectElement_;
	SelectColor_ = InInstance.SelectColor_;
	NormalColor_ = InInstance.NormalColor_;
	bIsSwitch_ = InInstance.bIsSwitch_;

	return *this;
}

const std::string& Menu::GetCurrentSelectElement() const
{
	return Elements_.at(CurrentSelectElement_);
}

void Menu::ProcessInput(const Input& InInput)
{
	bIsSwitch_ = false;

	if (InInput.GetKeyPressState(Input::EKeyType::Up) == Input::EPressState::Pressed)
	{
		MoveSelect(Menu::ESelectDirection::Up);
	}

	if (InInput.GetKeyPressState(Input::EKeyType::Down) == Input::EPressState::Pressed)
	{
		MoveSelect(Menu::ESelectDirection::Down);
	}

	if (InInput.GetKeyPressState(Input::EKeyType::Enter) == Input::EPressState::Pressed)
	{
		bIsSwitch_ = true;
	}
}

void Menu::MoveSelect(const ESelectDirection& InSelectDirection)
{
	int32_t CurrentElementSize = static_cast<int32_t>(Elements_.size());

	switch (InSelectDirection)
	{
	case ESelectDirection::Up:
		CurrentSelectElement_--;
		CurrentSelectElement_ = CurrentSelectElement_ < 0 ? (CurrentElementSize - 1) : (CurrentSelectElement_);
		break;

	case ESelectDirection::Down:
		CurrentSelectElement_++;
		CurrentSelectElement_ = CurrentSelectElement_ > (CurrentElementSize - 1) ? 0 : (CurrentSelectElement_);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined select direction");
	}
}

void Menu::Draw(const Vec2i& InPosition)
{
	Vec2i Position = InPosition;

	for (std::vector<std::string>::size_type ElementIndex = 0; ElementIndex < Elements_.size(); ++ElementIndex)
	{
		if (ElementIndex == CurrentSelectElement_)
		{
			Console::DrawText(Position.x, Position.y, Elements_[ElementIndex], SelectColor_);
		}
		else
		{
			Console::DrawText(Position.x, Position.y, Elements_[ElementIndex], NormalColor_);
		}

		Position.y += 1;
	}
}
