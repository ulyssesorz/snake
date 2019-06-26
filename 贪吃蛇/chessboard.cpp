#include"chessboard.h"

#define COL 44
#define ROW 22

HANDLE hOutput, hOutBuf;  //控制台屏幕缓冲区句柄
HANDLE *houtpoint;
COORD coord = { 1,5 };
DWORD bytes = 0;

chessboard::chessboard()
{

	for (i = 1; i <= H - 2; i++)
	{
		for (j = 1; j <= W - 2; j++)
		{
			qp[i][j] = ' ';//棋盘中间置零
		}
	}
	for (i = 0; i <= W - 1; i++)
	{
		qp[0][i] = qp[H - 1][i] = '#';//棋盘中间置#
	}
	for (i = 1; i <= H - 2; i++)
	{
		qp[i][0] = qp[i][W - 1] = '#';//棋盘中间置#
	}
	food(); //每次构造函数调用成员函数food生成食物
}
void chessboard::food()
{
	srand(time(0));      // 随机时间  srand生成随机数，需要输入随机种子，种子相同则随机数相同;为保证生成的随机数具有随机性应选取不同的随机种子，一般选取系统当前时间最为随机种子，因为系统时间在变化
						  //time(0)回去当前系统时间
	do
	{
		x1 = rand() % W - 2 + 1; // 随机位置
		y1 = rand() % H - 2 + 1;
	} while (qp[x1][y1] != ' '); //保证生成的食物在空白处
	qp[x1][y1] = '$'; //设置食物形状
}
void chessboard::prt(int grade, int score, int gamespeed)
{
	int i;
	int zhixiang_hOutput = 0;

	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,  //定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE, //定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,  //定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE, //定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	SetConsoleTitle(TEXT("贪吃蛇"));
	SMALL_RECT rc = { 0,0,COL + 10,ROW +10  };  //设置窗口大小，宽度和高度
	SetConsoleWindowInfo(hOutput, 1, &rc);
	SetConsoleWindowInfo(hOutBuf, 1, &rc);
	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	houtpoint = &hOutput;
	coord.Y = 1;
	coord.Y++;
	
	for (i = 0; i < ROW; i++) //显示结果
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