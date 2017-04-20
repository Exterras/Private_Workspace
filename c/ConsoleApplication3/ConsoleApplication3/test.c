#include <stdio.h>

void test01(void) {
	int a;
	double b;
	char c;

	printf("int ���� �ּ� : %u\n", &a);
	printf("double ���� �ּ� : %u\n", &b);
	printf("char ���� �ּ� : %u\n", &c);
}

void test02(void) {
	int a;
	int *pa;

	pa = &a;
	*pa = 10;

	printf("������ a�� ��� : %d\n", *pa);
	printf("���������� a�� ��� : %d\n", a);
}

void test03(void) {
	int a = 10;
	int b = 15;
	int tot;
	double avg;
	int *pa, *pb;
	int *pt = &tot;
	double *pg = &avg;

	pa = &a;
	pb = &b;

	*pt = *pa + *pb;
	*pg = *pt / 2.0;

	printf("�� ������ �� : %d, %d\n", *pa, *pb);
	printf("�� ������ �� : %d\n", *pt);
	printf("�� ������ ��� : %1lf\n", *pg);
}

void test04(void) {
	int a = 10;
	int *pa = &a;

	printf("%d\n", a);
	printf("%d\n", *pa);
}

int main(void) {
	test04();
	return 0;
}

