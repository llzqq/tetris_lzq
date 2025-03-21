
/*
define const values
*/

// ���崰�ڳ���
#define WINDOW_CAPTION		"Tetris"		// ���ڱ���
#define WINDOW_WIDTH		892				// ���ڿ��
#define WINDOW_HEIGHT		714				// ���ڸ߶�

// ������Ϸ����
#define GAME_AREA_LEFT		0				// ��Ϸ������߽�
#define GAME_AREA_RIGHT		612				// ��Ϸ�����ұ߽�
#define GAME_AREA_BOTTOM	714				// ��Ϸ�����±߽�

// ������Ϸ�ؿ�����ֵ
#define GAME_NUM_LEVELS		5				// ��Ϸ�ܹ���5���ؿ�
#define SCORE_PRE_LINE		125				// �������һ����ʱ��õķ���
#define SCORE_PRE_LEVEL		1300			// ����һ����Ҫ�ķ���

// ������Ϸ����ص�����
#define INITIAL_SPEED		60				// ����������ƶ��ļ��
#define SPEED_CHANGE		10				// ������һ��ʱ����Ϸ��������ٶȼӿ�

// ��Ϸ�鵽����Ϸ����ײ�ʱ���������һ�����ݵ�ʱ�䣬����������һ���
#define SLIDE_TIME			15

#define SQUARES_PER_ROW		18				// һ����18������
#define SQUARES_PER_COL		21				// һ����21������
#define SQUARES_MEDIAN		17				// �������ε����ĵ���ߵľ���

// ��Ϸ�飨����飩����ʼλ��
#define BLOCK_START_X		300
#define BLOCK_START_Y		72
// ��һ����Ϸ���λ��
#define NEXT_BLOCK_X		(612+155)
#define NEXT_BLOCK_Y		140

// ����÷֡�����ÿ������÷֡���ǰ��Ϸ��������ٶȵ�λ��
#define SCORE_POSITION_X	(612+60)		// ���Ƶ÷�λ��
#define SCORE_POSITION_Y	(65+180)
#define LEVEL_POSITION_X	(612+60)		// ��Ϸ����
#define LEVEL_POSITION_Y	300
#define SCORE_PER_LEVEL_X	(612+60)		// ÿ������÷�
#define SCORE_PER_LEVEL_Y	350
#define SPEED_X				(612+60)		// ��ǰ��Ϸ��������ٶȻ���λ��
#define SPEED_Y				400

// ����ͼƬ����λ��
#define BG1_POSITION_x		0				// ����ͼƬ1
#define BG1_POSITION_y		0
#define BG2_POSITION_x		612				// ����ͼƬ2
#define BG2_POSITION_y		0
#define BG3_POSITION_x		623				// ����ͼƬ2
#define BG3_POSITION_y		480