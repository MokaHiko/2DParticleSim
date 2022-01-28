#include "Water.h"

Water::Water(glm::vec2 pos, Texture2D& texture) : Element(pos, texture) { }

void Water::Update(Element* up, Element* down, Element* left, Element* right, Element* bLeft, Element* bRight, Element* tLeft, Element* tRight)
{
	glm::vec2 CurPos = GetPosition();
		if (GetPosition().y <= -71.0)
		{
			isBordered = true;
			SetPosition({ GetPosition().x, -71.0 });
		}
		else if (down == nullptr)
		{
			SetPosition({ CurPos.x, CurPos.y - 1 });
		}
		else
		{
			if(bLeft == nullptr)
			{
				SetPosition({ CurPos.x - 1, CurPos.y - 1 });
			}
			else if(bRight == nullptr)
			{
				SetPosition({ CurPos.x + 1, CurPos.y - 1 });
			}
			else
			{
				isBordered = true;
			}
		}

}
