#include "CellMatrix.h"

struct ElementsAround
{
	Element* Up;
	Element* Down;
	Element* Left;
	Element* Right;
	Element* BLeft;
	Element* BRight;
	Element* TLeft;
	Element* TRight;

	ElementsAround(Element* up, Element* down, Element* left, Element* right, Element* bLeft, Element* bRight, Element* tLeft, Element* tRight)
		: Up(up), Down(down), Left(left), Right(right), BLeft(bLeft), BRight(bRight), TLeft(tLeft), TRight(tRight) { }
};

CellMatrix::CellMatrix(SpriteRenderer* renderer, int _width, int _height, float _cellSize)
	: renderer(renderer), width(_width), height(_height), cellSize(_cellSize) { }

CellMatrix::~CellMatrix() { }

void CellMatrix::UpdateElements()
{
	for (Element* e : matrix)
	{
		glm::vec2 ePos = e->GetPosition();
		if (!(e->isBordered))
		{
			e->Update(	 get(ePos.x, ePos.y + 1),
						 get(ePos.x, ePos.y - 1),
						 get(ePos.x - 1, ePos.y),
						 get(ePos.x + 1, ePos.y),
						 get(ePos.x - 1, ePos.y - 1),
						 get(ePos.x + 1, ePos.y - 1),
						 get(ePos.x - 1, ePos.y + 1),
						 get(ePos.x + 1, ePos.y - 1));
		}
	}
}

void CellMatrix::AddElement(Element* e)
{
	matrix.push_back(e);
}

Element* CellMatrix::get(int x, int y)
{
	for (Element* e : matrix)
	{
		if (e->GetPosition() == glm::vec2(x, y))
		{
			return e;
		}
	}

	return nullptr;
}

void CellMatrix::CheckBorder(Element* e)
{

}

void CellMatrix::DrawElements()
{
	for(Element*  e : matrix)
	{
		renderer->DrawSprite(e->Texture, glm::vec2(e->GetPosition().x * cellSize, -e->GetPosition().y * cellSize), glm::vec2(cellSize)); // reverse because of coordinate system
	}
}


void CellMatrix::CleanElements()
{
	for (Element* e : matrix)
	{
		delete e;
	}
}
