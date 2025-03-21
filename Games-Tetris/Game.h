#pragma once

// ��Ϸ������Game
// �洢��Ϸ�е�������Ϸ�顢��ײ�����߼�

#include <time.h>
#include <math.h>
#include <vector>
#include <SDL_ttf.h>
#include "GameBlock.h"

using namespace std;

class Game
{
public:
	Game(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* Font);
	~Game(void);

public:
	// win the game
	// void Win();
	// fail the game
	// void Fail();
	// exit the game
	// void Exit();

public:
	// ��ʼ����Ϸ
	void Init();
	// ��ǰ��Ϸ���Զ������ƶ�
	void GameBlock_selfMove();
	// ���Ʒ���
	void Draw();
	void Draw_text(std::string message, int x, int y);
	// �ı佹���
	void ChangeFocusBlock();
	// ������ɵ�����
	int CalcCompleteRows();
	// �����������
	void HandleInput(Direction dir, bool IsUp);

// ��ײ����߼�
public:
	// �����Ϸ���Ƿ���Wall��ײ
	bool CheckWallCollisions(GameBlock* FocusGameBlock, Direction dir);
	bool CheckWallCollisions(Square* square, Direction dir);
	// �����Ϸ���Ƿ���������Ϸ����ײ
	bool CheckEntityCollisions(GameBlock* FocusGameBlock, Direction dir);
	bool CheckEntityCollisions(Square* square, Direction dir);
	// ������Ϸ�鲻�ƶ�ʱ���߼�
	void HandleStaticBlockCollision();
	// �����Ϸ����ת���Ƿ�����ײ
	bool CheckRotationCollisions(GameBlock* block);

private:
	GameBlock* FocusBlock;				// ��Ϸ������ڿ��ƵĿ�
	GameBlock* NextBlock;				// ��һ����Ϸ��
	vector<Square*> GameSquares;		// �洢��Ϸ�����еķ���

	// ��Ⱦ��
	SDL_Renderer* renderer;
	// ��������
	SDL_Texture* texture;
	// ����
	TTF_Font* Font;

	int Score;							// ��ҵ�ǰ�÷�
	int Level;							// ��ǰ��Ϸ�ȼ�
	int FocusBlockSpeed;				// ������ڿ��ƵĿ���ٶ�
};

