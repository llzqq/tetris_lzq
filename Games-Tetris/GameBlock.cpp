#include "stdafx.h"
#include "GameBlock.h"


GameBlock::GameBlock(void):
	texture(nullptr)
{
	center_x = 0;
	center_y = 0;
	// ��ʼ������ָ��Ϊnullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}
}

GameBlock::GameBlock(int center_x, int center_y, BlockType type, SDL_Texture* texture):
	type(type), texture(texture)
{
	this->center_x = center_x;
	this->center_y = center_y;
	// ��ʼ������ָ��Ϊnullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}

	SetupBlock(center_x, center_y, texture);
}

GameBlock::GameBlock(BlockType type, SDL_Texture* texture):
	type(type), texture(texture)
{
	center_x = 0;
	center_y = 0;
	// ��ʼ������ָ��Ϊnullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}
}

// ������Ϸ���������������ǵ���Ϸ��
void GameBlock::SetupBlock(int x, int y, SDL_Texture* texture)
{
	// ���ݸ�����λ�ú�������������Ϸ��
	center_x = x;
	center_y = y;
	
	// ���4�����飬��ֹ�ڴ�й©
	for (int i=0; i<4; ++i)
	{
		if (squares[i] != nullptr)
		{
			delete squares[i];
			squares[i] = nullptr;
		}
	}

	// ���ݸ�������Ϸ��������������Ϸ��
	switch (type)
	{
	case SQUARE_BLOCK:			// ������
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
		}
		break;
	case T_BLOCK:				// T��
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN * 3, y + SQUARES_MEDIAN, texture);
		}
		break;
	case L_BLOCK:				// L��
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case BACKWARDS_T_BLOCK:		// ����L��
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case STRAIGHT_BLOCK:		// ������
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN * 3, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case S_BLOCK:				// S��
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case BACKWARDS_S_BLOCK:		// ����S��
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	default:
		break;
	}
}

// ������Ϸ��
void GameBlock::DrawSquares(SDL_Renderer* renderer)
{
	// ����Square���е�DrawToRenderer����
	for (int i=0; i<4; ++i)
	{
		squares[i]->DrawToRenderer(renderer);
	}
}

// �ƶ���Ϸ��
void GameBlock::Move(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		center_x -= SQUARES_MEDIAN * 2;
		break;
	case RIGHT:
		center_x += SQUARES_MEDIAN * 2;
		break;
	case DOWN:
		center_y += SQUARES_MEDIAN * 2;
		break;
	default:
		break;
	}

	for (int i=0; i<4; ++i)
	{
		squares[i]->Move(dir);
	}
}

// ��ת���飬�����(0, 0)����ת90��
void GameBlock::Rotate()
{
	for (int i=0; i<4; ++i)
	{
		// ��ȡ��������λ��
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		// ���㷽����������Ϸ�����ĵ���Ծ���
		x -= center_x;
		y -= center_y;

		// ʵ����ת
		int x2 = -y;
		int y2 = x;

		// �������ƶ�����ȷλ��
		x2 += center_x;
		y2 += center_y;

		// �������÷�������λ��
		squares[i]->setCenter_x(x2);
		squares[i]->setCenter_y(y2);
	}
}

// ��ȡ��ת��ķ����ַ������ײ���
int* GameBlock::GetRotatedPositions()
{
	// �洢��ת��ķ����ַ
	int* SquaresPositions = new int[8];

	for (int i=0; i<4; ++i)
	{
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		x -= center_x;
		y -= center_y;

		int x2 = -y;
		int y2 = x;

		x2 += center_x;
		y2 += center_y;

		// ��¼������ת��ĵ�ַ
		SquaresPositions[i*2] = x2;
		SquaresPositions[i*2+1] = y2;
	}
	return SquaresPositions;
}

Square** GameBlock::GetSquares()
{
	return squares;
}

BlockType GameBlock::getBlockType() const
{
	return type;
}

GameBlock::~GameBlock(void)
{
	// �ͷŷ���������Դ
	//if (texture)
	//	SDL_DestroyTexture(texture);
	// �ͷ���Ϸ����Դ
	//for (int i=0; i<4; ++i)
	//{
	//	if (squares[i])
	//		delete squares[i];
	//}
}
