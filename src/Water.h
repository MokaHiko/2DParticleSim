#pragma once
#include "Element.h"

class Water : public Element
{
	public:
		Water(glm::vec2 pos, Texture2D& texture);
		void Update(Element* up, Element* down, Element* left, Element* right, Element* bLeft, Element* bRight, Element* tLeft, Element* tRight) override;
};



