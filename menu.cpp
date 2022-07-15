#include <stdio.h>
#include<windows.h>
#include<time.h>
#include "menu.h"
#include "game.h"
int speed = 1, key_num = 4, accur = 3;
pp head;
FILE* data_fp;
//以下是基本的操作函数
//隐藏光标
void hide_cursor()       				//隐藏光标 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

//移动光标位置，不管之前在哪里，直接到达x,y点，x是横轴，y是竖轴
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//清屏
void clr(void)
{
	system("cls");
}


//接下来是功能函数，即总和
//记住字的中间轴，为x = 49,50，从18行开始，一共4个选项
void menu()
{
	gotoxy(45, 10);
	printf("低仿钢琴块^w^\n（按w,s控制光标上下移动，回车来选中）");
	gotoxy(48, 18);
	printf("开始游戏");
	gotoxy(49, 23);
	printf("设置");
	gotoxy(48, 28);
	printf("本地记录");
	gotoxy(49, 33);
	printf("退出\n");
}

//记得在这里加歌，考虑用文件读取，以及增加自制谱子的功能？
void menu_music()
{
	gotoxy(35, 5);
	printf("■开始前请先耐心阅读游戏规则捏■");
	gotoxy(47, 10);
	printf("选择模式");
	gotoxy(43, 18);
	printf("bgm:两只老虎（迫真）");
	gotoxy(46, 23);
	printf("无声纯享版");
	gotoxy(46, 28);
	printf("魔改双向版");
	gotoxy(47, 33);
	printf("规则说明");
	gotoxy(49, 38);
	printf("返回");
}

//星标的打出，n表示打在第几行,num表示一共多少选项
void menu_select(int num, int n)
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (i == n)
		{
			gotoxy(35, 18 + i * 5);
			printf("-★-");
			gotoxy(64, 18 + i * 5);
			printf("-★-");
		}
		else
		{
			gotoxy(35, 18 + i * 5);
			printf("    ");
			gotoxy(64, 18 + i * 5);
			printf("    ");
		}
	}
}

//设置界面的展示
void menu_set()
{
	gotoxy(47, 10);
	printf("相关设置\n输入数字来调整难度，回车保存更改");
	gotoxy(48, 18);
	printf("速度\n\t\t\t\t\t(越大越快，区间是1-3)");
	gotoxy(46, 23);
	printf("判定严格度\n\t\t\t\t\t(越低越严格，区间1-3)");
	gotoxy(48, 28);
	printf("打击键个数\n\t\t\t\t\t\t(4,5,6)");
	gotoxy(48, 33);
	printf("返回");
}

//设置值的展示
void set_set(int ord, int num)
{
	if (num >= choose[ord][0] && num <= choose[ord][2])
	{
		gotoxy(60, 18 + ord * 5);
		printf("   ");
		printf("%d", num);
		if (ord == 0)
			speed = num;
		else if (ord == 1)
			accur = num;
		else
			key_num = num;
	}
}

void rules()
{
	gotoxy(47, 10);
	puts("*游戏说明*");
	gotoxy(15, 12);
	puts("目前做了3个模式，1个有bgm，2个无bgm，打击键对应的位置从1-6：a s d f g h");
	gotoxy(15, 14);
	puts("游戏停止条件：(1)按下空格后暂停，再按继续，或者esc退出(2)有bgm者是等所有音符全部产生后再结束，\n\t\t\t\t中间可以miss，无bgm是miss即结束");
	gotoxy(15, 16);
	puts("判定严格度说明：这个只决定miss判定的严格度，中央的蓝色粗线表示打击线，其两侧的灰色细线为击中判定区域");
	gotoxy(15, 18);
	puts("分数说明：只要不miss，就一定有至少50分，在未显示的规定区域内击中会增加得分");
	gotoxy(15, 20);
	puts("音符击中条件：以 *音符靠近打击线一侧的边缘* 进入打击区域时按下正确按键为击中");
	gotoxy(15, 22);
	puts("游戏结果会在结束后自动记录到游戏同根目录下的txt文件里，如果没有会自动创建捏");
	gotoxy(49, 28);
	printf("返回");
	gotoxy(50, 30);
	printf("游玩提示：设置判定严格度3，速度2-3以获得最佳体验(·ω<)☆");
	menu_select(3, 2);
}

void in_link(pp link, int i, int* list, char* tt)
{
	int j;
	for (j = 0; j < 7; j++)
		link->data[i][j] = list[j];
	strcpy(link->time[i], tt);
}

void add_data()
{
	int i;
	for (i = 0; i < 7; i++)
		fprintf(data_fp, "%d ", res[i]);
	fprintf(data_fp, "\n");
	time_t rawtime;
	struct tm* info;
	char buffer[80];
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y%m%e_%H%M%S", info);//以年月日_时分秒的形式表示当前时间
	fprintf(data_fp, "%s\n", buffer);
}

void store_data(void)
{
	rewind(data_fp);
	int i, j;
	char ti[30];
	int info[7];
	pp tmp = head;
	if (fscanf(data_fp, "%d %d %d %d %d %d %d", &info[0], &info[1], &info[2], &info[3], &info[4], &info[5], &info[6]) != EOF)
	{
		fgets(ti, 30, data_fp);
		fgets(ti, 30, data_fp);
		tmp->n = i = 1;
		in_link(tmp, 0, info, ti);
	}
	while (fscanf(data_fp, "%d %d %d %d %d %d %d", &info[0], &info[1], &info[2], &info[3], &info[4], &info[5], &info[6]) != EOF)
	{
		fgets(ti, 30, data_fp);
		fgets(ti, 30, data_fp);
		if (i < 9)
		{
			in_link(tmp, i, info, ti);
			tmp->n++;
			i = tmp->n;
		}
		else
		{
			pp new_page = (pp)malloc(sizeof(p));
			new_page->n = i = 0;
			in_link(new_page, i, info, ti);
			new_page->last = tmp;
			new_page->next = NULL;
			tmp->next = new_page;
			tmp = new_page;
			new_page->n = i = 1;
		}
	}
}

void read_data_new(pp pa)
{
	int i = 0, j;
	clr();
	gotoxy(48, 10);
	printf("历史记录");
	gotoxy(8, 12);
	puts("序号\t总分\t连击数\t最大连击\t模式\t速度\t判定准度\t打击键数\t\t时间");
	while (i < pa->n)
	{
		gotoxy(8, 14 + i * 2);
		printf("%d\t", i + 1);
		for (j = 0; j < 7; j++)
		{
			if (j == 3)
				printf("%s\t", mo[pa->data[i][j] - 1]);
			else if (j == 5)
				printf("%5d\t\t", pa->data[i][j]);
			else
				printf("%d\t", pa->data[i][j]);
		}
		printf("\t%s\n", pa->time[i]);
		i++;
	}
	gotoxy(49, 8);
	printf("-★-返回-★-                  按w/s来翻页");
}