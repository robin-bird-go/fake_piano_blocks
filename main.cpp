#include<windows.h>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "menu.h"
#include "game.h"


int main()
{

	char in;
	data_fp = fopen("./data.txt", "a+");
	int x = 0, tmp;//x表示开始菜单的选择结果，后面直接用于变量继续改值了
	srand(time(0));
	system("mode con cols=120 lines=40 ");//x<120,y<40
	while (1)
	{
		clr();
		hide_cursor();
		menu();
		menu_select(4, x);
		//这里是开始界面选择选项的显示部分
		while (1)
		{
			in = _getch();
			if (in == 'w')
				x = (x + (main_menu_choice - 1)) % main_menu_choice;
			else if (in == 's')
				x = (x + 1) % main_menu_choice;
			else if (in == 13)//回车表示选中
				break;
			menu_select(main_menu_choice, x);
		}
		if (x == 0)
		{
			while (1)
			{
				clr();
				hide_cursor();
				menu_music();
				menu_select(music_menu_choice, x);
				in = _getch();
				if (in == 'w')
					x = (x + (music_menu_choice - 1)) % music_menu_choice;
				else if (in == 's')
					x = (x + 1) % music_menu_choice;
				else if (x == 0 && in == 13)
				{
					sc = combo = mc = 0;
					initgraph(100 * key_num + 120, 650);
					create_screen(key_num, accur);
					game1(key_num, accur);
					closegraph();
					add_data();
				}
				else if (x == 1 && in == 13)
				{
					sc = combo = mc = 0;
					initgraph(100 * key_num + 120, 650);
					create_screen(key_num, accur);
					game2(key_num, accur);
					closegraph();
					add_data();
				}
				else if (x == 2 && in == 13)
				{
					sc = combo = mc = 0;
					initgraph(100 * key_num + 120, 650);
					game3(key_num, accur);
					closegraph();
					add_data();
				}
				else if (x == 3 && in == 13)
				{
					clr();
					x = 0;
					rules();
					while (1)
					{
						in = _getch();
						if (in == 13)
							break;
					}
				}
				else if (x == 4 && in == 13)//回车表示选中
					break;
				menu_select(music_menu_choice, x);
			}
			x = 0;
		}
		else if (x == 1)
		{
			x = 0;
			clr();
			menu_set();
			menu_select(set_menu_choice, 0);
			set_set(0, speed);
			set_set(1, accur);
			set_set(2, key_num);
			while (1)
			{
				in = _getch();
				if (in == 'w')
					x = (x + (set_menu_choice - 1)) % set_menu_choice;
				else if (in == 's')
					x = (x + 1) % set_menu_choice;
				else if (x != 3 && in == 13)
				{
					gotoxy(47, 39);
					printf("→请回车保存修改结果←");
					while ((in = _getch()) != 13)
					{
						tmp = _getch();
						set_set(x, tmp - '0');
					}
					gotoxy(47, 39);
					printf("                         ");
				}
				else if (x == 3 && in == 13)
					break;
				menu_select(set_menu_choice, x);
			}
			x = 1;
		}
		else if (x == 2)
		{
			head = (pp)malloc(sizeof(p));
			head->n = 0;
			head->next = NULL;
			head->last = NULL;
			pp tmp = head;
			store_data();
			read_data_new(tmp);		
			while (1)
			{
				in = _getch();
				if (in == 13)
				{
					tmp = head;
					pp l = head->next;
					while (l || tmp)
					{
						free(tmp);
						tmp = l;
						if(tmp)
							l = tmp->next;
					}
					break;
				}
				else if (in == 'w')
				{
					if (tmp->last)
					{
						tmp = tmp->last;
						read_data_new(tmp);
					}
				}
				else if (in == 's')
				{
					if (tmp->next)
					{
						tmp = tmp->next;
						read_data_new(tmp);
					}
				}
			}
			x = 0;
		}
		else if (x == 3)
			break;
	}
	fclose(data_fp);
	system("pause");
	return 0;
}

