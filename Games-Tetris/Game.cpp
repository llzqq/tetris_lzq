#include "stdafx.h"
#include "Game.h"


Game::Game(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* Font):
	FocusBlock(nullptr), NextBlock(nullptr), renderer(renderer),
	texture(texture), Font(Font)
{
	Score	= 0;
	Level	= 1;
	FocusBlockSpeed = INITIAL_SPEED;
}

// ��ʼ����Ϸ
void Game::Init()
{
	// ��ʼ�����������
	srand((unsigned int)time(0));
	// ��ʼ����Ϸ�飬λ�õ���Ϣ
	FocusBlock = new GameBlock(BLOCK_START_X, BLOCK_START_Y, (BlockType)(rand() % 7), texture);
	NextBlock = new GameBlock(NEXT_BLOCK_X, NEXT_BLOCK_Y, (BlockType)(rand() % 7), texture);
}

// ��ǰ��Ϸ�Զ������ƶ�
void Game::GameBlock_selfMove()
{
	// ��ǰ��Ϸ�������ƶ�ÿһ֡���߼�
	static int GameBlock_down_counter = 0;
	// ����ǰ��Ϸ���ƶ����ײ����߼�
	static int Slide_counter = SLIDE_TIME;

	// ����ǰ��Ϸ���Զ�����
	GameBlock_down_counter++;
	if (GameBlock_down_counter >= FocusBlockSpeed)
	{
		// ��Ϸ�������ƶ���Ҫ����ײ���
		if (!CheckWallCollisions(FocusBlock, DOWN) && 
			!CheckEntityCollisions(FocusBlock, DOWN))
		{
			FocusBlock->Move(DOWN);
			GameBlock_down_counter = 0;
		}
	}

	// ����ǰ��Ϸ���ƶ����ײ����߼�
	if (CheckWallCollisions(FocusBlock, DOWN) || 
		CheckEntityCollisions(FocusBlock, DOWN))
	{
		Slide_counter--;
	}
	else
	{
		Slide_counter = SLIDE_TIME;
	}
	
	if (Slide_counter == 0)
	{
		Slide_counter = SLIDE_TIME;
		HandleStaticBlockCollision();
	}

	// ����
	Draw();
}

// ���Ƶ�ǰ��Ϸ�顢��һ����Ϸ���Լ����з���
void Game::Draw()
{
	// ���Ƶ�ǰ��Ϸ�顢��һ����Ϸ��
	FocusBlock->DrawSquares(renderer);
	NextBlock->DrawSquares(renderer);
	// �������з���
	for (int i=0; i<GameSquares.size(); ++i)
	{
		GameSquares[i]->DrawToRenderer(renderer);
	}

	// ���Ƶ�ǰ�÷֡�������һ������÷֡�����
	char nex_square[50];
	sprintf_s(nex_square, "NEXT SQUARE:");
	Draw_text(nex_square, NEXT_BLOCK_X - 95, (NEXT_BLOCK_Y - 115));
	// �÷�
	char cur_score[50];
	sprintf_s(cur_score, "CURRENT SCORE: %d", Score);
	Draw_text(cur_score, SCORE_POSITION_X, SCORE_POSITION_Y);
	// ����
	char cur_level[50];
	sprintf_s(cur_level, "CURRENT LEVEL: %d", Level);
	Draw_text(cur_level, LEVEL_POSITION_X, LEVEL_POSITION_Y);
	// ÿ������÷�
	char level_score[50];
	sprintf_s(level_score, "SCORE OF LEVEL: %d", SCORE_PRE_LEVEL);
	Draw_text(level_score, SCORE_PER_LEVEL_X, SCORE_PER_LEVEL_Y);
	// ��ǰ��Ϸ�������ٶ�
	char cur_speed[50];
	sprintf_s(cur_speed, "CURRENT SPEED: %d", INITIAL_SPEED);
	Draw_text(cur_speed, SPEED_X, SPEED_Y);
}

void Game::Draw_text(std::string message, int x, int y)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(Font, message.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	int width = 0, height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		x, y, width, height
	};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// �����Ϸ���Ƿ���Wall��ײ
bool Game::CheckWallCollisions(GameBlock* FocusGameBlock, Direction dir)
{
	Square** squares = FocusGameBlock->GetSquares();
	for (int i=0; i<4; ++i)
	{
		if (CheckWallCollisions(squares[i], dir))
			return true;
	}

	return false;
}

bool Game::CheckWallCollisions(Square* square, Direction dir)
{
	// ÿ�ƶ�һ�εľ���
	int Distance = SQUARES_MEDIAN * 2;
	// ��ø������������
	int x = square->getCenter_x();
	int y = square->getCenter_y();

	bool result = false;
	switch (dir)
	{
	case LEFT:
		{
			if ((x - Distance) < GAME_AREA_LEFT)
				result = true;
			else
				result = false;
		}
		break;
	case RIGHT:
		{
			if ((x + Distance) > GAME_AREA_RIGHT)
				result = true;
			else
				result = false;
		}
		break;
	case DOWN:
		{
			if ((y + Distance) > GAME_AREA_BOTTOM)
				result = true;
			else
				result = false;
		}
		break;
	default:
		break;
	}

	return result;
}

bool Game::CheckEntityCollisions(Square* square, Direction dir)
{
	// ��������֮��ľ���
	int Distance = SQUARES_MEDIAN * 2;
	// ��ø������������
	int centerX = square->getCenter_x();
	int centerY = square->getCenter_y();

	switch (dir)
	{
	case LEFT:
		centerX -= Distance;
		break;
	case RIGHT:
		centerX += Distance;
		break;
	case DOWN:
		centerY += Distance;
		break;
	default:
		break;
	}
	// �����������Ƿ����������鷢����ײ
	for (int i=0; i<GameSquares.size(); ++i)
	{
		int x = GameSquares[i]->getCenter_x();
		int y = GameSquares[i]->getCenter_y();
		if ((abs(x - centerX) < Distance) && 
			(abs(y - centerY) < Distance))
		{
			return true;
		}
	}

	return false;
}

// �����Ϸ���Ƿ�����������ײ
bool Game::CheckEntityCollisions(GameBlock* FocusGameBlock, Direction dir)
{
	Square** squares = FocusGameBlock->GetSquares();
	for (int i=0; i<4; ++i)
	{
		if (CheckEntityCollisions(squares[i], dir))
			return true;
	}

	return false;
}

// ������Ϸ���ƶ����ײ�ʱ���߼�
void Game::HandleStaticBlockCollision()
{
	// �ı佹���
	ChangeFocusBlock();
	// �������ɵ�����
	int completeNums = CalcCompleteRows();

	if (completeNums > 0)
	{
		// �����õķ���
		Score += SCORE_PRE_LINE * completeNums;
		// �ж��Ƿ��ܽ�����һ��
		if (Score >= Level * SCORE_PRE_LEVEL)
		{
			Level++;
			// is Win?
			// ÿ������һ����Ϸ����ƶ��ٶȽ�������
			FocusBlockSpeed -= SPEED_CHANGE;
		}
	}

	// is Fail?

}

// ��⵱ǰ��Ϸ����ת���Ƿ�����ײ
bool Game::CheckRotationCollisions(GameBlock* block)
{
	// ��ȡ��ǰ��Ϸ����ת���λ��
	int* arr = block->GetRotatedPositions();
	// ������������֮��ľ���
	int Distance = SQUARES_MEDIAN * 2;

	// ���Wall�����еķ���
	for (int i=0; i<4; ++i)
	{
		// ���������Ϸ�߽�
		if (arr[i*2] < GAME_AREA_LEFT ||
			arr[i*2] > GAME_AREA_RIGHT)
		{
			delete arr;
			return true;
		}
		// �����Ϸ�·��߽�
		if (arr[i*2 + 1] > GAME_AREA_BOTTOM)
		{
			delete arr;
			return true;
		}
		// �����еķ���Ƚ�
		for (int j=0; j<GameSquares.size(); ++j)
		{
			if ((abs(arr[i*2] - GameSquares[j]->getCenter_x()) < Distance) && 
				(abs(arr[i*2+1] - GameSquares[j]->getCenter_y()) < Distance))
			{
				delete arr;
				return true;
			}
		}
	}

	delete arr;
	return false;
}

// �ı佹��飬ÿ�θı佹���ʱ��������Ҫ����ǰ������еķ�����뵽���з��鼯����
// ɾ������飬���ý�����Լ���һ����Ϸ��
void Game::ChangeFocusBlock()
{
	Square** squares = FocusBlock->GetSquares();
	// ��������еķ�����뵽���з��鼯����
	for (int i=0; i<4; ++i)
	{
		GameSquares.push_back(squares[i]);
	}
	// ɾ�������
	delete FocusBlock;
	// �������ý����
	FocusBlock = new GameBlock(NextBlock->getBlockType(), texture);
	FocusBlock->SetupBlock(BLOCK_START_X, BLOCK_START_Y, texture);
	// ������һ����Ϸ��
	delete NextBlock;
	NextBlock = new GameBlock(NEXT_BLOCK_X, NEXT_BLOCK_Y, (BlockType)(rand() % 7), texture);
}

// ������ɵ�����
int Game::CalcCompleteRows()
{
	// ����
	int bottomLine = GAME_AREA_BOTTOM - SQUARES_MEDIAN;
	// top line
	int topLine = SQUARES_MEDIAN;
	// ÿһ�еľ���
	int rowSize = SQUARES_MEDIAN * 2;
	// ��¼ÿ���з���ĸ���
	int SquareNums_per_row[21];
	for (int i=0; i<21; ++i)
	{
		SquareNums_per_row[i] = 0;
	}

	int row = 0, completeRows = 0;
	// Check for full lines
	for (int i=0; i<GameSquares.size(); ++i)
	{
		// ��õ���ǰ�������ڵ���
		int y = GameSquares[i]->getCenter_y();
		row = (y - topLine) / rowSize;
		SquareNums_per_row[row]++;
	}

	// Erase any full lines
	for (int line=0; line<21; ++line)
	{
		// �����ǰ�б���������
		if (SquareNums_per_row[line] == SQUARES_PER_ROW)
		{
			completeRows++;
			// ɾ�������������������еķ���
			for (int i=0; i<GameSquares.size(); ++i)
			{
				if (((GameSquares[i]->getCenter_y() - topLine) / rowSize) == line)
				{
					delete GameSquares[i];
					GameSquares.erase(GameSquares.begin() + i);
					i--;
				}
			}
		}
	}

	// ������������������з��������ƶ�
	for (int i=0; i<GameSquares.size(); ++i)
	{
		for (int line=0; line<21; ++line)
		{
			if (SquareNums_per_row[line] == SQUARES_PER_ROW)
			{
				int y = GameSquares[i]->getCenter_y();
				row = (y - topLine) / rowSize;
				if (line > row)
				{
					GameSquares[i]->Move(DOWN);
				}
			}
		}
	}

	return completeRows;
}

// ����������룬IsUp����ֻ�����Ϸ�����Ч
void Game::HandleInput(Direction dir, bool IsUp)
{
	// �������Ϸ��������ת��ǰ��Ϸ��
	if (IsUp)
	{
		if (!CheckRotationCollisions(FocusBlock))
			FocusBlock->Rotate();
	}
	else
	{
		if (!CheckWallCollisions(FocusBlock, dir) && 
			!CheckEntityCollisions(FocusBlock, dir))
		{
			FocusBlock->Move(dir);
		}
	}
}

Game::~Game(void)
{
	if (FocusBlock)
		delete FocusBlock;
	if (NextBlock)
		delete NextBlock;
	vector<Square*>::const_iterator it = GameSquares.begin();
	for (; it != GameSquares.end(); ++it)
	{
		const Square* del = (*it);
		if (del)
			delete del;
	}
	GameSquares.clear();
}
