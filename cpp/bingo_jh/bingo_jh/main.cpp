#include "header.h"

int main(void)
{
	int a = 1;
	srand(time(NULL));
	make_binggo user;
	p_b p_b;
	make_binggo com;
	get_result result;
	while (a)
	{
		p_b.Show_B_P(user, com);
		p_b.U_del_num(user, com);
		system("cls");
		p_b.Show_B_P(user, com);
		if (result.get_b_result(user, com) == 1)
		{
			break;
		}

		p_b.C_del_num(user, com);
		if (result.get_b_result(user, com) == 1)
		{
			break;
		}
		Sleep(1500);
		system("cls");
	}


	return 0;
}
