#include "bingo_jh.h"

class make_binggo
{
private:
	int binggo[5][5];
	int make_arr[25];
	int del_arr[25];
public:
	make_binggo()
	{
		int ax = 0;
		for (int i = 0; i < 25; i++)
		{
			make_arr[i] = i + 1;
		}

		for (int ax = 0; ax < 25; ax++)
		{
			int num = (rand() % 25);
			swap(make_arr[ax], make_arr[num]);
		}

		for (int dx = 0; dx < 5; dx++)
		{
			for (int cx = 0; cx < 5; cx++)
			{
				binggo[dx][cx] = make_arr[ax++];
			}
		}

	}
	int access_binggo(int i, int j)
	{
		return binggo[i][j];
	}
	void ch_b(int ax, int bx)
	{
		binggo[ax][bx] = -1;
	}
	int m_del_arr(void)
	{
		int ax = 0;
		int t = 0;
		for (int dx = 0; dx < 5; dx++)
		{
			for (int cx = 0; cx < 5; cx++)
			{
				if (binggo[dx][cx] != -1)
				{
					del_arr[ax++] = binggo[dx][cx];
					t++;
				}
			}
		}
		for (int i = 0; i < t; i++)
		{
			int num = (rand() % t);
			swap(del_arr[i], del_arr[num]);
		}

		return del_arr[0];

	}
	int access_del_num(int i)
	{
		return del_arr[i];
	}

};

class p_b
{
private:
	int u_num;
	int c_num;
	int num;

public:

	void U_del_num(make_binggo &a, make_binggo &b)
	{
		cout << "사용자 숫자 입력: ";
		cin >> u_num;
		num = u_num;
		for (int ax = 0; ax < 5; ax++)
		{
			for (int bx = 0; bx < 5; bx++)
			{
				if (a.access_binggo(ax, bx) == num)
				{
					a.ch_b(ax, bx);
				}
				if (b.access_binggo(ax, bx) == num)
				{
					b.ch_b(ax, bx);
				}
			}
		}

	}


	void C_del_num(make_binggo &a, make_binggo &b)
	{
		int num = a.m_del_arr();

		cout << "컴퓨터 숫자 입력: " << num << endl;

		for (int ax = 0; ax < 5; ax++)
		{
			for (int bx = 0; bx < 5; bx++)
			{
				if (a.access_binggo(ax, bx) == num)
				{
					a.ch_b(ax, bx);
				}
				if (b.access_binggo(ax, bx) == num)
				{
					b.ch_b(ax, bx);
				}
			}
		}
	}

	void Show_B_P(make_binggo a, make_binggo b)
	{
		cout << "   user            computer" << endl;
		for (int ax = 0; ax < 5; ax++)
		{
			for (int bx = 0; bx < 5; bx++)
			{
				if (a.access_binggo(ax, bx) == -1)
					cout << setw(3) << "X" << "  ";
				else

					cout << setw(3) << a.access_binggo(ax, bx) << "  ";
			}

			cout << "     ";
			for (int cx = 0; cx < 5; cx++)
			{
				if (b.access_binggo(ax, cx) == -1)
					cout << setw(3) << "X" << "  ";
				else
					cout << setw(3) << b.access_binggo(ax, cx) << "  ";
			}

			cout << endl;
		}

	}
};

class get_result
{
public:
	int get_b_result(make_binggo &a, make_binggo &b)
	{


		for (int ax = 0; ax < 5; ax++)
		{
			int s_u_cnt = 0;
			int s_c_cnt = 0;
			int g_u_cnt = 0;
			int g_c_cnt = 0;
			int d_u_cnt = 0;
			int d_u_cnt1 = 0;
			int d_c_cnt = 0;
			int d_c_cnt1 = 0;
			for (int bx = 0; bx < 5; bx++)
			{
				if (a.access_binggo(ax, bx) == -1)//사용자 가로
				{
					g_u_cnt++;
				}

				if (g_u_cnt == 5)
				{
					cout << "사용자 승리" << endl;
					return 1;
				}
				if (b.access_binggo(ax, bx) == -1)//컴퓨터 가로
				{
					g_c_cnt++;
				}

				if (g_c_cnt == 5)
				{
					cout << "컴퓨터 승리" << endl;
					return 1;
				}

				if (a.access_binggo(bx, ax) == -1)//사용자 세로
				{
					s_u_cnt++;
				}
				if (s_u_cnt == 5)
				{

					cout << "사용자 승리" << endl;
					return 1;
				}

				if (b.access_binggo(bx, ax) == -1)//컴퓨터 세로
				{
					s_c_cnt++;
				}
				if (s_c_cnt == 5)
				{

					cout << "컴퓨터 승리" << endl;
					return 1;
				}
				if (a.access_binggo(bx, bx) == -1)//사용자 대각선
				{
					d_u_cnt1++;
				}
				if (d_u_cnt1 == 5)
				{
					cout << "사용자 승리" << endl;
					return 1;
				}
				if (b.access_binggo(bx, bx) == -1)//컴퓨터 대각선
				{
					d_c_cnt1++;
				}
				if (d_c_cnt1 == 5)
				{
					cout << "컴퓨터 승리" << endl;
					return 1;
				}

				if (a.access_binggo(bx, 4 - bx) == -1)//사용자 대각선
				{
					d_u_cnt++;
				}
				if (d_u_cnt == 5)
				{
					cout << "사용자 승리" << endl;
					return 1;
				}
				if (b.access_binggo(bx, 4 - bx) == -1)//컴퓨터 대각선
				{
					d_c_cnt++;
				}
				if (d_c_cnt == 5)
				{
					cout << "컴퓨터 승리" << endl;
					return 1;
				}
			}
		}
	}
};


#endif
