#pragma once
#define main_menu_choice 4
#define music_menu_choice 5
#define set_menu_choice 4
typedef struct _page//每一页的数据
{
	int n;//这个表示存了多少行
	int data[9][7];
	char time[9][20];
	struct _page* last;
	struct _page* next;
}p, * pp;
extern pp head;
extern int speed, key_num, accur;//灵敏度，就是判定的严格程度
extern FILE* data_fp;
const int choose[3][3] = { {1,2,3},{1,2,3},{4,5,6} };
const char mo[3][20] = { "有bgm版本","无声纯享版","魔改双向版" };
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