#pragma once
#include"chessboard.h"

class snake :public chessboard // ��̳м��ɣ�����һ�º����������������̳кò��ã���
{
public:
	int zb[2][100]; //���ڴ��̰���ߵ�����
	long start; //���ڼ�ʱ
	int head, tail, grade, score, gamespeed, length, timeover, x, y; //��Ϸ��ʹ�õı���
	char direction;    //̰����ǰ������ASIC��������ʾ��ʽ
	char oldDirection; //����������õ�����ʱ����
	snake(); //���캯��
	void move();//��Ա����������̰�����ƶ�������ÿ500ms����һ��
};