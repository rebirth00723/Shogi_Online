﻿#include "piece.h"
// black : 1 red : 0
char* piece[2] = { { "帥仕仕相相硨硨傌傌炮炮兵兵兵兵兵" },{ "將士士象象車車馬馬包包卒卒卒卒卒" } };
void getPiece(int i, char* str, int color) {

	str[0] = piece[color][i * 2];
	str[1] = piece[color][i * 2 + 1];


}
char* getPiecer(int i, int color) {
	
	return &piece[color][i * 2];


}
// down : 1 up : 0
void  getPiece_pos(POS* p) {
				//　　將　　　士　　　士　　　象　　　象　　　車　　　車　　　馬　　　馬　　　包　　　包　　　卒　　　卒　　卒卒卒
	POS pos[16] = { { 9,4 },{ 9,3 },{ 9,5 },{ 9,2 },{ 9,6 },{ 9,0 },{ 9,8 },{ 9,1 },{ 9,7 },{ 7,1 },{ 7,7 },{ 6,0 },{ 6,2 },{ 6,4 },{ 6,6 },{ 6,8 } };


	for (int i = 0; i < 16; i++)
		p[i] = pos[i];
}

void getPiece_board_default(char** str)
{
	char* temp[25] = {
		//　　 ０　１　２　３　４　５　６　７　８
		"╔═════════════════════╗\n",//0
		"║　　　　　　　　　　　　　　　　　　　　起║\n",//1
		"║　　　　　　　　　　　　　　　　　　　　　║\n",//2
		"║　　硨─傌─相─仕─帥─仕─相─傌─硨　手║\n",//0   //9*10
		"║　　│　│　│　│╲│╱│　│　│　│　　║\n",
		"║　　├─┼─┼─┼─┼─┼─┼─┼─┤　無║\n",//1
		"║　　│　│　│　│╱│╲│　│　│　│　　║\n",
		"║　　├─炮─┼─┼─┼─┼─┼─炮─┤　悔║\n",//2
		"║　　│　│　│　│　│　│　│　│　│　　║\n",
		"║　　兵─┼─兵─┼─兵─┼─兵─┼─兵　大║\n",//3
		"║　　│　│　│　│　│　│　│　│　│　　║\n",
		"║觀　├─┴─┴─┴─┴─┴─┴─┴─┤　丈║\n",//4
		"║　　│　　楚　河　　　　　漢　界　　│　　║\n",
		"║棋　├─┬─┬─┬─┬─┬─┬─┬─┤　夫║\n",//5
		"║　　│　│　│　│　│　│　│　│　│　　║\n",
		"║不　卒─┼─卒─┼─卒─┼─卒─┼─卒　　║\n",//6
		"║　　│　│　│　│　│　│　│　│　│　　║\n",
		"║語　├─包─┼─┼─┼─┼─┼─包─┤　　║\n",//7
		"║　　│　│　│　│╲│╱│　│　│　│　　║\n",
		"║真　├─┼─┼─┼─┼─┼─┼─┼─┤　　║\n",//8
		"║　　│　│　│　│╱│╲│　│　│　│　　║\n",
		"║君　車─馬─象─士─將─士─象─馬─車　　║\n",//9
		"║　　　　　　　　　　　　　　　　　　　　　║\n",
		"║子　　　　　　　　　　　　　　　　　　　　║\n",
		"╚═════════════════════╝\n",

	};

	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 48; j++)
			str[i][j] = temp[i][j];
}

void getPiece_board_empty(char str[27][52])
{
	char* temp[27] = {
		"╔═══════════════════════╗\n",
		"║　　　　　　　　　　　　　　　　　　　　　　　║\n",
		"║　　　　　　　　　　　　　　　　　　　　　　起║\n",
		"║　　　０　１　２　３　４　５　６　７　８　　　║\n",
		"║　　Ａ┌─┬─┬─┬─┬─┬─┬─┬─┐　　手║\n",
		"║　　　│　│　│　│╲│╱│　│　│　│　　　║\n",
		"║　　Ｂ├─┼─┼─┼─┼─┼─┼─┼─┤　　無║\n",
		"║　　　│　│　│　│╱│╲│　│　│　│　　　║\n",
		"║　　Ｃ├─╬─┼─┼─┼─┼─┼─╬─┤　　悔║\n",
		"║　　　│　│　│　│　│　│　│　│　│　　　║\n",
		"║　　Ｄ╠─┼─╬─┼─╬─┼─╬─┼─╣　　大║\n",
		"║　　　│　│　│　│　│　│　│　│　│　　　║\n",
		"║觀　Ｅ├─┴─┴─┴─┴─┴─┴─┴─┤　　丈║\n",
		"║　　　│　　楚　河　　　　　漢　界　　│　　　║\n",
		"║棋　Ｆ├─┬─┬─┬─┬─┬─┬─┬─┤　　夫║\n",
		"║　　　│　│　│　│　│　│　│　│　│　　　║\n",
		"║不　Ｇ╠─┼─╬─┼─╬─┼─╬─┼─╣　　　║\n",
		"║　　　│　│　│　│　│　│　│　│　│　　　║\n",
		"║語　Ｈ├─╬─┼─┼─┼─┼─┼─╬─┤　　　║\n",
		"║　　　│　│　│　│╲│╱│　│　│　│　　　║\n",
		"║真　Ｉ├─┼─┼─┼─┼─┼─┼─┼─┤　　　║\n",
		"║　　　│　│　│　│╱│╲│　│　│　│　　　║\n",
		"║君　Ｊ└─┴─┴─┴─┴─┴─┴─┴─┘　　　║\n",
		"║　　　０　１　２　３　４　５　６　７　８　　　║\n",
		"║子　　　　　　　　　　　　　　　　　　　　　　║\n",
		"║　　　　　　　　　　　　　　　　　　　　　　　║\n",
		"╚═══════════════════════╝\n",

	};

	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 52; j++)
			str[i][j] = temp[i][j];


}
