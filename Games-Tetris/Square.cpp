#include "stdafx.h"
#include "Square.h"


Square::Square(void):
	texture(nullptr)
{
	center_x = 0;
	center_y = 0;
}

Square::Square(int center_x, int center_y, SDL_Texture* texture):
	texture(texture)
{
	this->center_x = center_x;
	this->center_y = center_y;
}

// ���Ƶ���������
void Square::DrawToRenderer(SDL_Renderer* renderer)
{
	SDL_Rect rect = {
		this->center_x - SQUARES_MEDIAN, this->center_y - SQUARES_MEDIAN,
		SQUARES_MEDIAN * 2, SQUARES_MEDIAN * 2
	};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// ���������ε��ƶ�
void Square::Move(Direction dir)
{
	switch (dir)
	{
	case LEFT:		// �����ƶ�
		center_x -= SQUARES_MEDIAN * 2; 
		break;
	case RIGHT:		// �����ƶ�
		center_x += SQUARES_MEDIAN * 2;
		break;
	case DOWN:		// �����ƶ�
		center_y += SQUARES_MEDIAN * 2;
		break;
	default:
		break;
	}
}

Square::~Square(void)
{
	//if (texture != nullptr)
	//	SDL_DestroyTexture(texture);
}
