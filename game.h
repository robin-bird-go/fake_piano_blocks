#pragma once
#define ac_unit 5
#define line_color RGB(193,193,193)
#define hit_line_color RGB(153,217,234)
#define grey_b_color RGB(160,160,160)
#define _32time  50//32分音符18毫秒
const char key[6] = { 'a','s','d','f','g','h' };
const int sound[3][13] = { {0,262,277,294,311,330,349,370,392,415,440,466,494},
	{0,523,554,578,622,659,698,740,784,831,880,932,988},
	{0,1046,1109,1175,1245,1318,1397,1480,1568,1661,1760,1865,1976}
};//以1-12有效，0无效哈
const int sp[4] = { 0,1,3,5 };//这个是表示填充用的无声方块数量，1-3对应speed
extern int sc, mc, combo, res[7];
extern FILE* fp;
typedef struct _block
{
	int x;//这个是左下角的坐标
	int y;
	int fre;
	int time;
	struct _block* next;
}b, * pb;
typedef struct _queue
{
	pb head;
	pb tail;
	int num;
}que, * qq;
extern qq q;
void create_screen(int n, int ac);
void create_screen2(int n, int ac);
void in_queue(pb nb);
void out_queue();
void display_b(pb bl);
void hit_b(pb bl);
void hit_b23(pb bl);
void init_block1(int n);
void init_block2(int n);
void init_block3(int n);
void get_block1(int n);
void get_block2(int n);
void get_block3(int n);
void output_words(int n);
int judge_score12(pb bl);
int judge_score3(int n, pb bl);
void game1(int n, int ac);
void game2(int n, int ac);
void game3(int n, int ac);