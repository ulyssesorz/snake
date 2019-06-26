#include"snake.h"

snake::snake()
{
	cout << "\n\n\t\tThe game is about to begin!" << endl;
	for (i = 3; i >= 0; i--) // 321����ʱ
	{
		start = clock();     //��Ա������ʼ��ʱ
		while (clock() - start <= 1000); // ��ͣ1000��ϵͳʱ��Ƭ��1��
		system("cls");
		if (i > 0)
			cout << "\n\n\t\tCountdown:" << i << endl;
	}
	for (i = 1; i <= 3; i++) // ����̰������ʼ����λ��
	{
		qp[1][i] = '*';//̰��������
	}
	qp[1][4] = '@';     //̰����ͷ
	for (i = 0; i < 4; i++) //��ʼ��̰���ߵ�����
	{
		zb[0][i] = 1;
		zb[1][i] = i + 1;
	}
}
void snake::move()
{
	score = 0;
	head = 3, tail = 0;
	grade = 1, length = 4;
	gamespeed = 500; // 500ʱ��Ƭ0.5����һ��
	direction = 77; // ��ʼ����-��
	oldDirection = direction;
	int breakFlag = 0; //�����쳣��־
	while (1)
	{
		timeover = 1;
		start = clock(); //��ʱ��ʼ
		while ((timeover = (clock() - start <= gamespeed)) && !_kbhit()); //�ȴ�gamespeedʱ���Զ�ǰ�������а�������ǰ��
		//���ȴ�ʱ�䳬��gamespeed��(timeover = (clock() - start <= gamespeed)Ϊ���˳�whileѭ���������������У���ʱtimeover=0,��ʾ�Զ�ǰ��
		//���а������룬_kbhit()λ�棬��_kbhit()Ϊ�٣������������У���ʱtimeover=1,��ʾ���������ֶ�ǰ��
		if (timeover)
		{
			_getch();//����Ϊ���������ҡ�ʱ����Ҫ��ȡ���β��ܵõ���ȷ��ASC�� 
			direction = _getch();//��ȥ���뷽��
			//��д����������������ʱ�����ȴ��¸�������Ϊ��ͣЧ��
		}
		switch (direction) //���ݷ���̰���ߵ�������� 
		{
			//�뵱ǰǰ�������෴������Ϊ�����쳣
		case 72:if (oldDirection == 80) { breakFlag = 1; break; }x = zb[0][head] - 1; y = zb[1][head]; oldDirection = direction; break;//�������
		case 80: if (oldDirection == 72) { breakFlag = 1; break; }x = zb[0][head] + 1; y = zb[1][head]; oldDirection = direction; break;//�������
		case 75: if (oldDirection == 77) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] - 1; oldDirection = direction; break;//�������
		case 77: if (oldDirection == 75) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] + 1; oldDirection = direction; break;//�������
		default: breakFlag = 1;//�����������ҷ�Χ�İ�����Ϊ�����쳣
		}

		if (breakFlag) //�����쳣����
		{
			switch (oldDirection) {//����ԭ�з������ǰ��
			case 72: x = zb[0][head] - 1; y = zb[1][head]; direction = oldDirection; break;//�������
			case 80: x = zb[0][head] + 1; y = zb[1][head]; direction = oldDirection; break;//�������
			case 75: x = zb[0][head]; y = zb[1][head] - 1; direction = oldDirection; break;//�������
			case 77: x = zb[0][head]; y = zb[1][head] + 1; direction = oldDirection; break;//�������
			}
			breakFlag = 0; //�ָ���־λ
		}
		if (x == 0 || x == 21 || y == 0 || y == 43) // �ж��Ƿ�ײǽ
		{
			cout << "\tGame over!" << endl; break;
		}
		if (qp[x][y] != ' ' && !(x == x1 && y == y1)) // ���Լ��ж�
		{
			cout << "\tGame over!" << endl; break;
		}
		if (x == x1 && y == y1) // �Ե��ʵ�
		{
			length++;
			score = score + 100;
			if (length >= 8)
			{
				length -= 8;
				grade++;
				if (gamespeed >= 200)
					gamespeed = 550 - grade * 50; //��Ϸ�Ѷȵȼ����ã�����
			}
			qp[x][y] = '@';
			qp[zb[0][head]][zb[1][head]] = '*';
			head = (head + 1) % 100;
			zb[0][head] = x;
			zb[1][head] = y;
			food();//��������ʳ��
			prt(grade, score, gamespeed); //������Ļ��ʾ
		}
		else
		{
			qp[zb[0][tail]][zb[1][tail]] = ' ';
			tail = (tail + 1) % 100;
			qp[zb[0][head]][zb[1][head]] = '*';
			head = (head + 1) % 100;
			zb[0][head] = x;
			zb[1][head] = y;
			qp[zb[0][head]][zb[1][head]] = '@';
			prt(grade, score, gamespeed);//������Ļ��ʾ
		}
	}
}