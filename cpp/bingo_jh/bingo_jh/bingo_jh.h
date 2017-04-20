#ifndef __BINGGO__
#define __BINGGO__

#include <iostream>
#include <time.h>
#include <iomanip>
#include <windows.h>
#pragma warning(disable:4996)
using namespace std;
#define swap(a,b) do{int t;t=a;a=b;b=t;}while(0)

class make_binggo
{
private:
	int binggo[5][5];
	int make_arr[25];
	int del_arr[25];
public:
	make_binggo();
	int access_binggo(int i, int j);
	void ch_b(int ax, int bx);
	int m_del_arr(void);
	int access_del_num(int i);
};

class p_b
{
private:
	int u_num;
	int c_num;
	int num;
public:
	void U_del_num(make_binggo &a, make_binggo &b);
	void C_del_num(make_binggo &a, make_binggo &b);
	void Show_B_P(make_binggo a, make_binggo b);
};

class get_result
{
public:
	int get_b_result(make_binggo &a, make_binggo &b);
};


#endif
