#pragma once

// Square���ʾ���������Σ����ĸ�square�����Ϸ��
// ����Ϸ��ÿ����һ��ʱ������Ŀ�������ƶ�����˶���һ��square����������ǵ���Ϸ����Ӻ���

#include <SDL.h>
#include "Defines.h"
#include "Enums.h"

class Square
{
public:
	Square(void);
	Square(int center_x, int center_y, SDL_Texture* texture);
	~Square(void);

public:
	// ���Ƶ���������
	void DrawToRenderer(SDL_Renderer* renderer);
	// �����������ε��ƶ�
	void Move(Direction dir);

// ���ʺ��޸����Եķ���
public:
	// �������Է���
	int getCenter_x() const { return center_x; }
	int getCenter_y() const { return center_y; }
	// �������Է���
	void setCenter_x(int center_x) { this->center_x = center_x; }
	void setCenter_y(int center_y) { this->center_y = center_y; }
	void setTexture(SDL_Texture* texture) { this->texture = texture; }

private:
	// �洢���������ε�����λ��
	int center_x;					// ����x����
	int center_y;					// ����y����
	
	SDL_Texture* texture;			// �洢������������������
};

