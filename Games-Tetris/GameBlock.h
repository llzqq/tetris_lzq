#pragma once

// ��������Ϸ�е���Ϸ�飬���ĸ�square���
// ������Enums.h�ļ��ж�����������Ϸ�����ͣ�������Ҫ����ָ������Ϸ��������
// �������ǵ���Ϸ��������״

#include "Square.h"

class GameBlock
{
public:
	GameBlock(void);
	GameBlock(int center_x, int center_y, BlockType type, SDL_Texture* texture);
	GameBlock(BlockType type, SDL_Texture* texture);
	~GameBlock(void);

public:
	// ������Ϸ���������������ǵ���Ϸ��
	void SetupBlock(int x, int y, SDL_Texture* texture);
	// ������Ϸ��
	void DrawSquares(SDL_Renderer* renderer);
	// �ƶ���Ϸ��
	void Move(Direction dir);
	// ��ת����
	void Rotate();
	// ��ȡ��ת������λ��
	int* GetRotatedPositions();
	BlockType getBlockType() const;

	Square** GetSquares();

private:
	// ��Ϸ������λ��
	int center_x;			// ����x����
	int center_y;			// ����y����

	BlockType type;			// ��Ϸ������
	SDL_Texture* texture;	// ������Ϸ����״��С����������
	Square* squares[4];		// �����Ϸ���4��ָ������
};

