#include <stdio.h>
#include<windows.h>
#include<time.h>
#include "menu.h"
#include "game.h"
int speed = 1, key_num = 4, accur = 3;
pp head;
FILE* data_fp;
//�����ǻ����Ĳ�������
//���ع��
void hide_cursor()       				//���ع�� 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

//�ƶ����λ�ã�����֮ǰ�����ֱ�ӵ���x,y�㣬x�Ǻ��ᣬy������
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//����
void clr(void)
{
	system("cls");
}


//�������ǹ��ܺ��������ܺ�
//��ס�ֵ��м��ᣬΪx = 49,50����18�п�ʼ��һ��4��ѡ��
void menu()
{
	gotoxy(45, 10);
	printf("�ͷ¸��ٿ�^w^\n����w,s���ƹ�������ƶ����س���ѡ�У�");
	gotoxy(48, 18);
	printf("��ʼ��Ϸ");
	gotoxy(49, 23);
	printf("����");
	gotoxy(48, 28);
	printf("���ؼ�¼");
	gotoxy(49, 33);
	printf("�˳�\n");
}

//�ǵ�������Ӹ裬�������ļ���ȡ���Լ������������ӵĹ��ܣ�
void menu_music()
{
	gotoxy(35, 5);
	printf("����ʼǰ���������Ķ���Ϸ�������");
	gotoxy(47, 10);
	printf("ѡ��ģʽ");
	gotoxy(43, 18);
	printf("bgm:��ֻ�ϻ������棩");
	gotoxy(46, 23);
	printf("���������");
	gotoxy(46, 28);
	printf("ħ��˫���");
	gotoxy(47, 33);
	printf("����˵��");
	gotoxy(49, 38);
	printf("����");
}

//�Ǳ�Ĵ����n��ʾ���ڵڼ���,num��ʾһ������ѡ��
void menu_select(int num, int n)
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (i == n)
		{
			gotoxy(35, 18 + i * 5);
			printf("-��-");
			gotoxy(64, 18 + i * 5);
			printf("-��-");
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

//���ý����չʾ
void menu_set()
{
	gotoxy(47, 10);
	printf("�������\n���������������Ѷȣ��س��������");
	gotoxy(48, 18);
	printf("�ٶ�\n\t\t\t\t\t(Խ��Խ�죬������1-3)");
	gotoxy(46, 23);
	printf("�ж��ϸ��\n\t\t\t\t\t(Խ��Խ�ϸ�����1-3)");
	gotoxy(48, 28);
	printf("���������\n\t\t\t\t\t\t(4,5,6)");
	gotoxy(48, 33);
	printf("����");
}

//����ֵ��չʾ
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
	puts("*��Ϸ˵��*");
	gotoxy(15, 12);
	puts("Ŀǰ����3��ģʽ��1����bgm��2����bgm���������Ӧ��λ�ô�1-6��a s d f g h");
	gotoxy(15, 14);
	puts("��Ϸֹͣ������(1)���¿ո����ͣ���ٰ�����������esc�˳�(2)��bgm���ǵ���������ȫ���������ٽ�����\n\t\t\t\t�м����miss����bgm��miss������");
	gotoxy(15, 16);
	puts("�ж��ϸ��˵�������ֻ����miss�ж����ϸ�ȣ��������ɫ���߱�ʾ����ߣ�������Ļ�ɫϸ��Ϊ�����ж�����");
	gotoxy(15, 18);
	puts("����˵����ֻҪ��miss����һ��������50�֣���δ��ʾ�Ĺ涨�����ڻ��л����ӵ÷�");
	gotoxy(15, 20);
	puts("���������������� *�������������һ��ı�Ե* ����������ʱ������ȷ����Ϊ����");
	gotoxy(15, 22);
	puts("��Ϸ������ڽ������Զ���¼����Ϸͬ��Ŀ¼�µ�txt�ļ�����û�л��Զ�������");
	gotoxy(49, 28);
	printf("����");
	gotoxy(50, 30);
	printf("������ʾ�������ж��ϸ��3���ٶ�2-3�Ի���������(����<)��");
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
	strftime(buffer, 80, "%Y%m%e_%H%M%S", info);//��������_ʱ�������ʽ��ʾ��ǰʱ��
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
	printf("��ʷ��¼");
	gotoxy(8, 12);
	puts("���\t�ܷ�\t������\t�������\tģʽ\t�ٶ�\t�ж�׼��\t�������\t\tʱ��");
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
	printf("-��-����-��-                  ��w/s����ҳ");
}