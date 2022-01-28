#pragma once
#include<vector>

#include "Element.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
class CellMatrix
{
public:
	CellMatrix(SpriteRenderer* renderer, int _width, int _height, float _cellSize = 10.0f);
	~CellMatrix();
	
	void UpdateElements();
	void AddElement(Element* e);

	int inline getNumberOfElements() { return matrix.size(); }

	// set functions
	Element* get(int x, int y);
	void CheckBorder(Element* e);

	void DrawElements();
	void CleanElements();

	float cellSize; 
private:
	std::vector<Element*> matrix;
	int width, height;

	SpriteRenderer* renderer;
	
};

