#include"chessboard.h"

#define COL 44
#define ROW 22

HANDLE hOutput, hOutBuf;  //����̨��Ļ���������
HANDLE *houtpoint;
COORD coord = { 1,5 };
DWORD bytes = 0;

chessboard::chessboard()
{

	for (i = 1; i <= H - 2; i++)
	{
		for (j = 1; j <= W - 2; j++)
		{
			qp[i][j] = ' ';//�����м�����
		}
	}
	for (i = 0; i <= W - 1; i++)
	{
		qp[0][i] = qp[H - 1][i] = '#';//�����м���#
	}
	for (i = 1; i <= H - 2; i++)
	{
		qp[i][0] = qp[i][W - 1] = '#';//�����м���#
	}
	food(); //ÿ�ι��캯�����ó�Ա����food����ʳ��
}
void chessboard::food()
{
	srand(time(0));      // ���ʱ��  srand�������������Ҫ����������ӣ�������ͬ���������ͬ;Ϊ��֤���ɵ���������������Ӧѡȡ��ͬ��������ӣ�һ��ѡȡϵͳ��ǰʱ����Ϊ������ӣ���Ϊϵͳʱ���ڱ仯
						  //time(0)��ȥ��ǰϵͳʱ��
	do
	{
		x1 = rand() % W - 2 + 1; // ���λ��
		y1 = rand() % H - 2 + 1;
	} while (qp[x1][y1] != ' '); //��֤���ɵ�ʳ���ڿհ״�
	qp[x1][y1] = '$'; //����ʳ����״
}
void chessboard::prt(int grade, int score, int gamespeed)
{
	int i;
	int zhixiang_hOutput = 0;

	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,  //������̿�����������д����
		FILE_SHARE_WRITE, //���建�����ɹ���дȨ��
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,  //������̿�����������д����
		FILE_SHARE_WRITE, //���建�����ɹ���дȨ��
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	SetConsoleTitle(TEXT("̰����"));
	SMALL_RECT rc = { 0,0,COL + 10,ROW +10  };  //���ô��ڴ�С����Ⱥ͸߶�
	SetConsoleWindowInfo(hOutput, 1, &rc);
	SetConsoleWindowInfo(hOutBuf, 1, &rc);
	//���������������Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	houtpoint = &hOutput;
	coord.Y = 1;
	coord.Y++;
	
	for (i = 0; i < ROW; i++) //��ʾ���
	{			
		coord.Y++;
		WriteConsoleOutputCharacterA(*houtpoint, (char *)qp[i], COL, coord, &bytes);		
	}
	SetConsoleActiveScreenBuffer(*houtpoint);
	for (i = 0; i < ROW; i++) 
	{
		
		cout << "\t";
		if (i == 0) cout << "\tGrade:" << grade;
		if (i == 1) cout << "\tScore:" << score;
		if (i == 2) cout << "\ttime interval:" << gamespeed << "ms";
		cout << endl;
	}
}