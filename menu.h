#pragma once
#define main_menu_choice 4
#define music_menu_choice 5
#define set_menu_choice 4
typedef struct _page//ÿһҳ������
{
	int n;//�����ʾ���˶�����
	int data[9][7];
	char time[9][20];
	struct _page* last;
	struct _page* next;
}p, * pp;
extern pp head;
extern int speed, key_num, accur;//�����ȣ������ж����ϸ�̶�
extern FILE* data_fp;
const int choose[3][3] = { {1,2,3},{1,2,3},{4,5,6} };
const char mo[3][20] = { "��bgm�汾","���������","ħ��˫���" };
void gotoxy(int x, int y);
void menu();
void menu_music();
void menu_select(int num, int n);
void hide_cursor();
void clr(void);
void menu_set();
void set_set(int ord, int num);
void rules();
void add_data();
void in_link(pp link, int i, int* list, char* tt);
void store_data(void);
void read_data_new(pp pa);