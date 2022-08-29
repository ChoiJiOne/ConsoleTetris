#include "Macro.h"
#include "Menu.h"

Menu::Menu(const Console::ETextColor& InSelectColor, const Console::ETextColor& InNormalColor)
	: SelectColor(InSelectColor)
	, NormalColor(InNormalColor)
	, CurrentSelectElement(0)
{
}

Menu::Menu(Menu&& InInstance) noexcept
	: Elements(InInstance.Elements)
	, CurrentSelectElement(InInstance.CurrentSelectElement)
	, SelectColor(InInstance.SelectColor)
	, NormalColor(InInstance.NormalColor)
{
}

Menu::Menu(const Menu& InInstance) noexcept
	: Elements(InInstance.Elements)
	, CurrentSelectElement(InInstance.CurrentSelectElement)
	, SelectColor(InInstance.SelectColor)
	, NormalColor(InInstance.NormalColor)
{
}

Menu::~Menu()
{
}

Menu& Menu::operator=(Menu&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Elements = InInstance.Elements;
	CurrentSelectElement = InInstance.CurrentSelectElement;
	SelectColor = InInstance.SelectColor;
	NormalColor = InInstance.NormalColor;

	return *this;
}

Menu& Menu::operator=(const Menu& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	Elements = InInstance.Elements;
	CurrentSelectElement = InInstance.CurrentSelectElement;
	SelectColor = InInstance.SelectColor;
	NormalColor = InInstance.NormalColor;

	return *this;
}

void Menu::AddElement(const std::string& InName)
{
	Elements.push_back(InName);
}

const std::string& Menu::GetCurrentSelectElement() const
{
	if (Elements.empty())
	{
		return std::string("");
	}
	else
	{
		return Elements[CurrentSelectElement];
	}
}

void Menu::MoveSelect(const ESelectDirection& InSelectDirection)
{
	switch (InSelectDirection)
	{
	case ESelectDirection::Up:
		CurrentSelectElement = (CurrentSelectElement - 1) % (Elements.size());
		break;

	case ESelectDirection::Down:
		CurrentSelectElement = (CurrentSelectElement + 1) % (Elements.size());
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined select direction");
	}
}

void Menu::Draw(const Math::Vec2i& InPosition)
{
	if (Elements.empty())
	{
		return;
	}

	Math::Vec2i Position = InPosition;

	for (std::vector<std::string>::size_type CurrentElementIndex = 0; CurrentElementIndex < Elements.size(); ++CurrentElementIndex)
	{
		if (CurrentElementIndex == CurrentSelectElement)
		{
			Console::DrawText(Position.x, Position.y, Elements[CurrentElementIndex], SelectColor);
		}
		else
		{
			Console::DrawText(Position.x, Position.y, Elements[CurrentElementIndex], NormalColor);
		}

		Position.y += 1;
	}
}
