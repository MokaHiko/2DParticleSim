#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
class Element
{
public:
	Element(glm::vec2 pos, Texture2D& texture) : Position(pos), isBordered(false), Texture(texture) { }
	
	virtual void Update(Element* up, Element* down, Element* left, Element* right, Element* bLeft, Element* bRight, Element* tLeft, Element* tRight) { }

	inline glm::vec2 GetPosition() { return Position; }
	inline void SetPosition(glm::vec2 newPos) { Position = newPos;}

	bool isBordered;
	Texture2D& Texture;
private:
	glm::vec2 Position;
};

