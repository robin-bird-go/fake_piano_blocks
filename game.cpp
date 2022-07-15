#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include "game.h"
#include "menu.h"
int sc = 0;
int mc = 0;
int combo = 0;
int res[7];//�������7��
qq q = (qq)malloc(sizeof(que));
FILE* fp = fopen("./babybaby.txt2", "r");
//550�Ǵ��������
//n��ʾ�Ǽ�����������Ϸ,ac��׼�����䣬Ҳ���Ǻ��ж��й�,Խ���Ѷ�Խ��
void create_screen(int n, int ac)
{
	setbkcolor(WHITE);
	cleardevice();
	int i;
	setlinecolor(line_color);
	for (i = 1; i <= n; i++)
		line(100 * i, 0, 100 * i, 650);
	line(0, 550 - ac * ac * ac_unit, 100 * n, 550 - ac * ac * ac_unit);
	line(0, 550 + ac * ac * ac_unit, 100 * n, 550 + ac * ac * ac_unit);
	setfillcolor(hit_line_color);
	fillrectangle(0, 547, 100 * n, 553);
	setlinecolor(RED);
	line(0, 550, 100 * n, 550);
}
void create_screen2(int n, int ac)
{
	setbkcolor(WHITE);
	cleardevice();
	int i;
	setlinecolor(line_color);
	for (i = 1; i <= n; i++)
		line(100 * i, 0, 100 * i, 650);
	line(0, 550 - ac * ac * ac_unit, 100 * (n / 2), 550 - ac * ac * ac_unit);
	line(0, 550 + ac * ac * ac_unit, 100 * (n / 2), 550 + ac * ac * ac_unit);
	line(100 * (n / 2), 100 - ac * ac * ac_unit, 100 * n, 100 - ac * ac * ac_unit);
	line(100 * (n / 2), 100 + ac * ac * ac_unit, 100 * n, 100 + ac * ac * ac_unit);
	setfillcolor(hit_line_color);
	fillrectangle(0, 547, 100 * (n / 2), 553);
	fillrectangle(100 * (n / 2), 97, 100 * n, 103);
	setlinecolor(RED);
	line(0, 550, 100 * (n / 2), 550);
	line(100 * (n / 2), 100, 100 * n, 100);
}
//��Ӳ�����������ǰѷ�����ʧ����������ʾ��
void in_queue(pb nb)
{
	q->tail->next->next = nb;
	q->tail->next = nb;
	q->num++;
}
void out_queue()
{
	pb tmp = q->head->next;
	q->head->next = tmp->next;
	free(tmp);
	q->num--;
}

void display_b(pb bl)
{
	if (bl->y <= 0 || bl == NULL)
		return;
	setfillcolor(BLACK);
	int  t = bl->y - 110 > 0 ? bl->y - 110 : 0, b = bl->y > 650 ? 650 : bl->y, l = bl->x, r = bl->x + 100;
	fillrectangle(l, t, r, b);
}
//�ɹ����з���
void hit_b(pb bl)
{
	if (bl->fre > 0)
		Beep(bl->fre, bl->time);
	int  t = bl->y - 110 > 0 ? bl->y - 110 : 0, b = bl->y > 650 ? 650 : bl->y, l = bl->x, r = bl->x + 100;
	setfillcolor(grey_b_color);
	fillrectangle(l, t, r, b);
	out_queue();
}

//�ɹ����з���
void hit_b23(pb bl)
{
	out_queue();
}

void output_words(int n)
{
	char tmp[30];
	settextcolor(BLACK);
	settextstyle(20, 10, _T("Consolas"));
	outtextxy(100 * n + 10, 110, _T("score:"));
	sprintf(tmp, "%d", sc);
	outtextxy(100 * n + 30, 140, tmp);
	outtextxy(100 * n + 10, 170, _T("combo:"));
	sprintf(tmp, "%d", combo);
	outtextxy(100 * n + 30, 200, tmp);
	outtextxy(100 * n + 10, 230, _T("1:a"));
	outtextxy(100 * n + 10, 250, _T("2:s"));
	outtextxy(100 * n + 10, 270, _T("3:d"));
	outtextxy(100 * n + 10, 290, _T("4:f"));
	outtextxy(100 * n + 10, 310, _T("5:g"));
	outtextxy(100 * n + 10, 330, _T("6:h"));
	outtextxy(100 * n + 10, 400, _T("press blank"));
	outtextxy(100 * n + 10, 420, _T("to pause"));
}

//n��ʾ��������������Ҫ��Ϊ����
//�����������֣����Ӷ�ȡ��txt+fsanf������ÿ��������+������32������Ϊ1��Խ�����γ�2����ͣ����00 ʱ��
void init_block1(int n)
{
	q = (qq)malloc(sizeof(que));
	q->head = (pb)malloc(sizeof(b));
	q->tail = (pb)malloc(sizeof(b));
	q->head->next = q->tail->next = NULL;
	q->num = 0;
	pb nb;
	int j, k;
	while (q->num < 6)
	{
		nb = (pb)malloc(sizeof(b));
		if (fscanf(fp, "%d %d %d", &j, &k, &(nb->time)) != EOF)
		{
			nb->fre = sound[j][k];
			nb->time *= _32time;//�����ʾ�������ʱ��,���ٶ��޹�
			nb->y = (4 - q->num) * 110;
			nb->x = (rand() % n) * 100;
			nb->next = NULL;
			if (q->num == 0)
			{
				q->head->next = q->tail->next = nb;
				q->num = 1;
			}
			else
				in_queue(nb);
			int i = nb->time /**speed*/ / (_32time * 4);//��ʾ���ˢ�����ķ������
			while (i)
			{
				nb = (pb)malloc(sizeof(b));
				nb->fre = nb->time = 0;
				nb->y = (4 - q->num) * 110;
				nb->x = (rand() % n) * 100;
				nb->next = NULL;
				in_queue(nb);
				i--;
			}
		}
	}
}

//n��ʾ��������������Ҫ��Ϊ����
void init_block2(int n)
{
	q = (qq)malloc(sizeof(que));
	q->head = (pb)malloc(sizeof(b));
	q->tail = (pb)malloc(sizeof(b));
	q->head->next = q->tail->next = NULL;
	q->num = 0;
	pb nb;
	nb = (pb)malloc(sizeof(b));
	nb->y = (4 - q->num) * 110;
	nb->x = (rand() % n) * 100;
	nb->next = NULL;
	q->head->next = q->tail->next = nb;
	q->num = 1;

	int i = 5;
	while (i)
	{
		nb = (pb)malloc(sizeof(b));
		nb->y = (4 - q->num) * 110;
		nb->x = (rand() % n) * 100;
		nb->next = NULL;
		in_queue(nb);
		i--;
	}
}
void init_block3(int n)
{
	q = (qq)malloc(sizeof(que));
	q->head = (pb)malloc(sizeof(b));
	q->tail = (pb)malloc(sizeof(b));
	q->head->next = q->tail->next = NULL;
	q->num = 0;
	pb nb;
	nb = (pb)malloc(sizeof(b));
	nb->x = (rand() % n) * 100;
	if ((nb->x / 100 + 1) > (n / 2))
		nb->y = 760 - ((4 - q->num) * 110);
	else
		nb->y = (4 - q->num) * 110;
	nb->next = NULL;
	q->head->next = q->tail->next = nb;
	q->num = 1;

	int i = 5;
	while (i)
	{
		nb = (pb)malloc(sizeof(b));
		nb->x = (rand() % n) * 100;
		if ((nb->x / 100 + 1) > (n / 2))
			nb->y = 760 - ((4 - q->num) * 110);
		else
			nb->y = (4 - q->num) * 110;
		nb->next = NULL;
		in_queue(nb);
		i--;
	}
}
//������ȡ�µķ��飬���з��������ʣ��ʱ��������6�����ϵķ��鵱������Ŀ<=6,��ʼ������ȡ����
void get_block1(int n)
{
	int j, k;
	pb nb = (pb)malloc(sizeof(b));
	while (q->num <= 6 && fscanf(fp, "%d %d %d", &j, &k, &(nb->time)) != EOF)
	{
		nb->fre = sound[j][k];
		nb->time *= _32time;//�����ʾ�������ʱ��,���ٶ��޹�
		nb->y = /*(5 - q->num) * 110;*/ q->tail->next->y - 110;
		nb->x = (rand() % n) * 100;
		nb->next = NULL;
		in_queue(nb);
		int i = nb->time /** speed*/ / (_32time * 4);//��ʾ���ˢ�����ķ������
		while (i)
		{
			nb = (pb)malloc(sizeof(b));
			nb->fre = nb->time = 0;
			nb->y = /*(5 - q->num) * 110;*/q->tail->next->y - 110;
			nb->x = (rand() % n) * 100;
			nb->next = NULL;
			in_queue(nb);
			i--;
		}
	}
}

//������ȡ�µķ��飬���з��������ʣ��ʱ��������6�����ϵķ��鵱������Ŀ<=6,��ʼ������ȡ����
void get_block2(int n)
{
	pb nb = (pb)malloc(sizeof(b));
	nb->y = q->tail->next->y - 110;
	nb->x = (rand() % n) * 100;
	nb->next = NULL;
	in_queue(nb);
}

void get_block3(int n)
{
	pb nb = (pb)malloc(sizeof(b)), tmp = q->tail->next;
	nb->x = (rand() % n) * 100;

	if ((tmp->x / 100 + 1) > (n / 2))
	{
		if ((nb->x / 100 + 1) > (n / 2))
			nb->y = tmp->y + 110;
		else
			nb->y = 650 - tmp->y;
	}
	else
	{
		if ((nb->x / 100 + 1) > (n / 2))
			nb->y = 870 - tmp->y;
		else
			nb->y = tmp->y - 110;
	}
	nb->next = NULL;
	in_queue(nb);
}

int judge_score12(pb bl)
{
	int num = (int)fabs(bl->y - 550);
	if (num < 3)
		return 15;
	else if (num < 10)
		return 10;
	else
		return 5;
}
int judge_score3(int n, pb bl)
{
	int num;
	if (bl->x / 100 + 1 > (n / 2))
		num = (int)fabs(bl->y - 100);
	else
		num = (int)fabs(bl->y - 550);
	if (num < 3)
		return 15;
	else if (num < 10)
		return 10;
	else
		return 5;
}
void game1(int n, int ac)
{
	//�Ȱѳ�ʼ������������
	init_block1(n);
	pb tmp = q->head->next;
	int now = 1;
	while (tmp && now <= 6)
	{
		display_b(tmp);
		tmp = tmp->next;
		now++;
	}
	//������������˵�����������������ʼ��
	settextcolor(BLACK);
	outtextxy(300, 300, "press_any_buttom_to_start");
	system("pause");
	char in = 0;
	int c, flag = 0;
	//��ʼ��ʽ
	while (1)
	{
		output_words(n);
		if (q->head->next == NULL)
			break;
		while (q->head->next->y < 550 + ac * ac * ac_unit)
		{
			in = 0;
			if (q->head->next->y >= 550 - ac * ac * ac_unit)
				in = _kbhit();
			if (in != 0)
				break;
			cleardevice();
			BeginBatchDraw();
			pb tmp = q->head->next;
			create_screen(n, ac);
			while (tmp)
			{
				display_b(tmp);
				tmp->y += 3 * speed;
				tmp = tmp->next;
			}
			output_words(n);
			FlushBatchDraw();
			Sleep(20);
		}
		in = _getch();
		if (in == 32)
		{
			while (1)
			{
				in = _getch();
				if (in == 32)
					break;
				else
				{
					flag = 3;
					if (mc < combo)
						mc = combo;
					break;
				}
			}
		}
		if (flag == 3)
			break;
		if (q->head->next->y >= 550 + ac * ac * ac_unit)
		{
			if (mc < combo)
				mc = combo;
			combo = 0;
			out_queue();
		}
		else if (in && q->head->next->y >= 550 - ac * ac * ac_unit)
		{
			c = q->head->next->x / 100;
			if (in == key[c])
			{
				sc += judge_score12(q->head->next);
				combo++;
				hit_b(q->head->next);
			}
			else
			{
				int j = 0;
				for (j = 0; j < n; j++)
				{
					if (j != c)
					{
						if (key[j] == in)
						{
							if (mc < combo)
								mc = combo;
							combo = 0;
							out_queue();
						}
					}
				}
			}
		}
		if (q->num < 6)
			get_block1(n);
		else if (q->num == 0)
			break;
	}
	EndBatchDraw();
	settextcolor(BLACK);
	settextstyle(20, 17, _T("Consolas"));
	if (flag != 3)
		outtextxy(50, 300, _T("thxxxx for playing!��\\(^u^)�Ρ�"));
	else
		outtextxy(50, 300, _T("ooooops~~QWQ"));
	outtextxy(50, 400, _T("press_blank_space_to_return"));
	while (1)
	{
		if ((in = _getch()) == 32)
			break;
	}
	res[0] = sc;
	res[1] = combo;
	res[2] = mc;
	res[3] = 1;
	res[4] = speed;
	res[5] = ac;
	res[6] = n;
}
void game2(int n, int ac)
{
	//�Ȱѳ�ʼ������������
	init_block2(n);
	pb tmp = q->head->next;
	int now = 1;
	while (tmp && now <= 6)
	{
		display_b(tmp);
		tmp = tmp->next;
		now++;
	}
	//������������˵�����������������ʼ��
	settextcolor(BLACK);
	outtextxy(300, 300, "press_any_buttom_to_start");
	system("pause");
	char in = 0;
	int c, flag = 0;
	//��ʼ��ʽ
	while (1)
	{
		output_words(n);
		if (q->head->next == NULL)
			break;
		while (q->head->next->y < 550 + ac * ac * ac_unit)
		{
			in = 0;
			if (q->head->next->y >= 550 - ac * ac * ac_unit)
				in = _kbhit();
			if (in != 0)
				break;
			cleardevice();
			BeginBatchDraw();
			pb tmp = q->head->next;
			create_screen(n, ac);
			while (tmp)
			{
				display_b(tmp);
				tmp->y += 3 * speed;
				tmp = tmp->next;
			}
			output_words(n);
			FlushBatchDraw();
			Sleep(20);
		}
		in = _getch();
		if (in == 32)
		{
			while (1)
			{
				in = _getch();
				if (in == 32)
					break;
				else
				{
					flag = 3;
					if (mc < combo)
						mc = combo;
					break;
				}
			}
		}
		if (flag == 3)
			break;
		if (q->head->next->y >= 550 + ac * ac * ac_unit)
		{
			if (mc < combo)
				mc = combo;
			combo = 0;
			flag = 1;
			break;
		}
		else if (in && q->head->next->y >= 550 - ac * ac * ac_unit)
		{
			c = q->head->next->x / 100;
			if (in == key[c])
			{
				sc += judge_score12(q->head->next);
				combo++;
				hit_b23(q->head->next);
			}
			else
			{
				int j = 0;
				for (j = 0; j < n; j++)
				{
					if (j != c)
					{
						if (key[j] == in)
						{
							if (mc < combo)
								mc = combo;
							combo = 0;
							flag = 1;
							break;
						}
					}
				}
			}
		}
		if (q->num < 6)
			get_block2(n);
		else if (q->num == 0)
			break;
	}
	EndBatchDraw();
	if (flag == 0)
	{
		settextcolor(BLACK);
		settextstyle(20, 17, _T("Consolas"));
		outtextxy(50, 300, _T("thxxxx for playing!��\\(^u^)�Ρ�"));
		outtextxy(50, 400, _T("press_blank_space_to_return"));
	}
	else
	{
		settextcolor(BLACK);
		settextstyle(20, 17, _T("Consolas"));
		outtextxy(50, 300, _T("ooooops~~QWQ"));
		outtextxy(50, 400, _T("press_blank_space_to_return"));
	}
	while (1)
	{
		if ((in = _getch()) == 32)
			break;
	}
	res[0] = sc;
	res[1] = combo;
	res[2] = mc;
	res[3] = 2;
	res[4] = speed;
	res[5] = ac;
	res[6] = n;
}
void game3(int n, int ac)
{
	BeginBatchDraw();
	create_screen2(n, ac);
	//�Ȱѳ�ʼ������������
	init_block3(n);
	pb tmp = q->head->next;
	int now = 1;
	while (tmp && now <= 6)
	{
		display_b(tmp);
		tmp = tmp->next;
		now++;
	}
	//������������˵�����������������ʼ��
	settextcolor(BLACK);
	outtextxy(300, 300, "press_any_buttom_to_start");
	FlushBatchDraw();
	system("pause");
	char in = 0;
	int c, flag = 0;
	pb h;
	//��ʼ��ʽ
	while (1)
	{
		output_words(n);
		h = q->head->next;
		if (h == NULL)
			break;
		while ((h->x / 100 + 1 <= (n / 2) && h->y < 550 + ac * ac * ac_unit) || (h->x / 100 + 1 > (n / 2) && h->y-110 > 100 - ac * ac * ac_unit))
		{
			in = 0;
			if ((h->x / 100 + 1 <= (n / 2) && h->y >= 550 - ac * ac * ac_unit) || (h->x / 100 + 1 > (n / 2) && h->y-110 <= 100 + ac * ac * ac_unit))
				in = _kbhit();
			if (in != 0)
				break;
			cleardevice();
			BeginBatchDraw();
			pb tmp = q->head->next;
			create_screen2(n, ac);
			while (tmp)
			{
				display_b(tmp);
				if (tmp->x / 100 + 1 > (n / 2))
					tmp->y -= 3 * speed;
				else
					tmp->y += 3 * speed;
				tmp = tmp->next;
			}
			output_words(n);
			FlushBatchDraw();
			Sleep(20);
		}
		in = _getch();
		if (in == 32)
		{
			while (1)
			{
				in = _getch();
				if (in == 32)
					break;
				else
				{
					flag = 3;
					if (mc < combo)
						mc = combo;
					break;
				}
			}
		}
		if (flag == 3)
			break;
		if ((h->x / 100 + 1 <= (n / 2) && h->y >= 550 + ac * ac * ac_unit) || (h->x / 100 + 1 > (n / 2) && h->y-110 <= 100 - ac * ac * ac_unit))
		{
			if (mc < combo)
				mc = combo;
			combo = 0;
			flag = 1;
			break;
		}
		else if (in && ((h->x / 100 + 1 <= (n / 2) && h->y >= 550 - ac * ac * ac_unit) || (h->x / 100 + 1 > (n / 2) && h->y-110 <= 100 + ac * ac * ac_unit)))
		{
			c = h->x / 100;
			if (in == key[c])
			{
				sc += judge_score3(n, h);
				combo++;
				hit_b23(h);
				h = q->head->next;
			}
			else
			{
				int j = 0;
				for (j = 0; j < n; j++)
				{
					if (j != c)
					{
						if (key[j] == in)
						{
							if (mc < combo)
								mc = combo;
							combo = 0;
							flag = 1;
							break;
						}
					}
				}
			}
		}
		if (q->num < 6)
			get_block3(n);
		else if (q->num == 0)
			break;
	}
	EndBatchDraw();
	settextcolor(RGB(0, 162, 232));
	settextstyle(19, 15, _T("Consolas"));
	outtextxy(50, 300, _T("23333333~~~~(^_^)/(T_T)"));
	outtextxy(50, 400, _T("press_blank_space_to_return"));
	while (1)
	{
		if ((in = _getch()) == 32)
			break;
	}
	res[0] = sc;
	res[1] = combo;
	res[2] = mc;
	res[3] = 3;
	res[4] = speed;
	res[5] = ac;
	res[6] = n;
}