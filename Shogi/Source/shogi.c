#include "shogi.h"	
#include "math.h"
#include "windows.h"


int checkNoPiece(shogi s, POS pos)
{

	for (int j = 0; j < PIECE_AMOUNT; j++)
		
		if ((s.pos[1][j].x == pos.x) && (s.pos[1][j].y == pos.y)) 
			return 0;

	return 1;
}
shogi initShogi(int isblack) {
	shogi s;

	s.isblack = isblack;

	getPiece_pos(s.pos[0]);
	getPiece_pos(s.pos[1]);

	s.print = print;
	s.showSurvive = showSurvive;
	s.move = move;
	return s;
}

void kill(shogi * s, POS pos, struct sending *S)
{
	S->move.x = pos.x;
	S->move.y = pos.y;
	S->dead = -1;
	for (int i = 0; i < PIECE_AMOUNT; i++) {
		int X = 9 - s->pos[0][i].x;
		int Y = s->pos[0][i].y;
		if ( X == pos.x && Y == pos.y) {
			S->dead = i;
			s->pos[0][i].x = -1;
			s->pos[0][i].y = -1;
		}
	}
	return send;
}

int  move(shogi* s, int id, int x, int y, struct sending* S)
{
	POS pos = s->pos[1][id];
	POS pos2 = { x, y };
	int val = 0;

	if (x > 9 || x < 0 || y < 0 || y > 8)//超越框架
		return 0;

	if (s->pos[1][id].x == x && s->pos[1][id].y == y)//沒有移動
		return 0;

	val = checkNoPiece(*s, pos2);//移動點沒有我方旗子

	if (val == 0)
		return 0;

	if (id == 0)
		val = gerneral(*s, pos, pos2);
	else if (id < 3)
		val = knight(*s, pos, pos2);
	else if (id < 5)
		val = elephant(*s, pos, pos2);
	else if (id < 7)
		val = car(*s, pos, pos2);
	else if (id < 9)
		val = horse(*s, pos, pos2);
	else if (id < 11)
		val = cannon(*s, pos, pos2);
	else
		val = soldier(*s, pos, pos2);

	if (val == 1) {
		S->id = id;
		kill(s, pos2, S);
		s->pos[1][id] = pos2;
	}
		
	return val;
}


int offset(int pos)
{
	pos = 4 + pos * 2;
	return pos;
}

void print(shogi s) {

	char _board[27][52], str[2];
	int X, x, Y, y;
	getPiece_board_empty(_board);

	for (int i = 0; i < 16; i++) {
	
		X = offset(s.pos[1][i].x);
		Y = offset(s.pos[1][i].y) * 2;
		x = offset(9 - s.pos[0][i].x);
		y = offset(s.pos[0][i].y) * 2;
	
		if (s.pos[1][i].x != -1 || s.pos[1][i].y != -1) {
			getPiece(i, str, s.isblack);
			_board[X][Y] = str[0];
			_board[X][Y + 1] = str[1];
		}

		if (s.pos[0][i].x != -1 || s.pos[0][i].y != -1) {
			getPiece(i, str, !s.isblack);
			_board[x][y] = str[0];
			_board[x][y + 1] = str[1];
		}
	}

	for (int i = 0; i < sizeof(_board) / (sizeof(*_board)); i++)
		printf("%s", _board[i]);
		
	
}

void showSurvive(shogi s)
{
	int i = 0;
	for (; i < 3; i++) {
	
		if (s.pos[1][i].x != -1) {
			char piece[2] = {0};
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)　", i, piece[0], piece[1],  'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}

	printf("\n");

	for (; i < 11; i++) {

		if (s.pos[1][i].x != -1) {
			char piece[2] = { 0 };
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)　", i, piece[0], piece[1], 'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}

	printf("\n");

	for (; i < 16; i++) {

		if (s.pos[1][i].x != -1) {
			char piece[2] = { 0 };
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)　", i, piece[0], piece[1], 'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}
	printf("\n");
}

int gerneral(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;

	if (y < 3 || y>5 || x > 9 || x < 7)
		return 0;

	if ((	abs(pos.x - x) == 1 && pos.y == y)
	|| (	abs(pos.y - y) == 1 && pos.x == x))
		return 1;
		
	return 0;
}

int knight(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;
	
	if (y < 3 || y>5 || x > 9 || x < 7)
		return 0;

	if (abs(pos.x - x) == 1 && abs(pos.y - y) == 1)
		return 1;

	return 0;
}

int elephant(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;
	if(x > 5)
		if (abs(pos.x - x) == 2 && abs(pos.y - y) == 2)
			return 1;

	return 0;
}

int car(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;
	int X = pos.x;
	int Y = pos.y;
	if (X == x || Y == y) {
		if (X == x) {//橫著走

			for (int j = 0; j < 2; j++)
				for (int i = 0; i < PIECE_AMOUNT; i++) {

					int px = s.pos[j][i].x;
					int py = s.pos[j][i].y;

					if (j == 0)
						px = 9 - px;
					if (px == x) {
						if ((y - Y) > 0) { // 向右
							if (py > Y && py < y) {
								return 0;
							}
						}
						else {//向左
							if (py < Y && py > y) {
								return 0;
							}
						}
					}
				}

		}
		else {
			if (Y == y) {//職著走

				for (int j = 0; j < 2; j++)
					for (int i = 0; i < PIECE_AMOUNT; i++) {

						int px = s.pos[j][i].x;
						int py = s.pos[j][i].y;

						if (j == 0)
							px = 9 - px;
						if (py == y) {
							if ((x - X) > 0) { // 向下
								if (px < x && px > X) {
									return 0;
								}
							}
							else {//向上
								if (px > x && px < X) {
									return 0;
								}
							}
						}
					}
			}//判別中間障礙物
		}
		return 1;
	}
	return 0;
}

int horse(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;

	if ((abs(pos.x - x) == 2 && abs(pos.y - y) == 1)
		|| (abs(pos.x - x) == 1 && abs(pos.y - y) == 2)) 
		return 1;
	
	return 0;
}

int soldier(shogi s, POS pos, POS pos2)
{
	int x = pos2.x;
	int y = pos2.y;

	if (pos.x - x == 1 && pos.y == y)
		return 1;

	if(pos.x < 5)//已在對岸
		if (pos.x == x && abs(pos.y - y) == 1)
			return 1;

	return 0;
}

int cannon(shogi s, POS pos, POS pos2)
{
	int X = pos.x;
	int Y = pos.y;
	int x = pos2.x;
	int y = pos2.y;

	int Obstacle = 0;
	if (X == x || Y == y) {
		if (X == x) {//橫著走

			for (int j = 0; j < 2; j++)
				for (int i = 0; i < PIECE_AMOUNT; i++) {

					int px = s.pos[j][i].x;
					int py = s.pos[j][i].y;

					if (j == 0)
						px = 9 - px;
					if (px == x) {
						if ((y - Y) > 0) { // 向右
							if (py > Y && py < y) {
								Obstacle++;
								if (Obstacle > 1)//太多障礙物
									return 0;
							}
						}
						else {//向左
							if (py < Y && py > y) {
								Obstacle++;
								if (Obstacle > 1)//太多障礙物
									return 0;
							}
						}
					}
				}

		}
		else
			if (Y == y) {//職著走

				for (int j = 0; j < 2; j++)
					for (int i = 0; i < PIECE_AMOUNT; i++) {

						int px = s.pos[j][i].x;
						int py = s.pos[j][i].y;

						if (j == 0)
							px = 9 - px;
						if (py == y) {
							if ((x - X) > 0) { // 向下
								if (px < x && px > X) {
									Obstacle++;
									if (Obstacle > 1)//太多障礙物
										return 0;
								}
							}
							else {//向上
								if (px > x && px < X) {
									Obstacle++;
									if (Obstacle > 1)//太多障礙物
										return 0;
								}
							}
						}
					}
			}//判別中間障礙物
			 //如果只有一個障礙物
		if (Obstacle) {
			for (int i = 0; i < PIECE_AMOUNT; i++) {

				int px = 9 - s.pos[0][i].x;
				int py = s.pos[0][i].y;

				if (px == x && py == y)//如果有敵人
					return 1;
			}
			return 0;
		}
		else {
			for (int j = 0; j < 2; j++)
				for (int i = 0; i < PIECE_AMOUNT; i++) {

					int px = s.pos[j][i].x;
					int py = s.pos[j][i].y;

					if (j == 0)
						px = 9 - px;

					if (px == x && py == y)//如果有人 失敗
						return 0;
				}
			return 1;
		}

	}
	
	
	return 0;
}

int noObstacle(shogi s, POS pos, POS pos2)
{
	return 0;
}
