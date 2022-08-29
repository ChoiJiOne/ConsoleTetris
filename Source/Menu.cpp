#include "Macro.h"
#include "Menu.h"

Menu::Menu(
	const std::vector<std::string>& InElements, 
	const Console::ETextColor& InSelectColor, 
	const Console::ETextColor& InNormalColor
): Elements(InElements),
   SelectColor(InSelectColor), 
   NormalColor(InNormalColor), 
   CurrentSelectElement(0)
{
	CHECK((Elements.size() > 0), "number of menu is 0");
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

const std::string& Menu::GetCurrentSelectElement() const
{
	return Elements[CurrentSelectElement];
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
	Math::Vec2i Position = InPosition;

	for (std::vector<std::string>::size_type ElementIndex = 0; ElementIndex < Elements.size(); ++ElementIndex)
	{
		if (ElementIndex == CurrentSelectElement)
		{
			Console::DrawText(Position.x, Position.y, Elements[ElementIndex], SelectColor);
		}
		else
		{
			Console::DrawText(Position.x, Position.y, Elements[ElementIndex], NormalColor);
		}

		Position.y += 1;
	}
}
