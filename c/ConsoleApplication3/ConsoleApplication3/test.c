#include <stdio.h>

void test01(void) {
	int a;
	double b;
	char c;

	printf("int 변수 주소 : %u\n", &a);
	printf("double 변수 주소 : %u\n", &b);
	printf("char 변수 주소 : %u\n", &c);
}

void test02(void) {
	int a;
	int *pa;

	pa = &a;
	*pa = 10;

	printf("포인터 a값 출력 : %d\n", *pa);
	printf("변수명으로 a값 출력 : %d\n", a);
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

	printf("두 정수의 값 : %d, %d\n", *pa, *pb);
	printf("두 정수의 합 : %d\n", *pt);
	printf("두 정수의 평균 : %1lf\n", *pg);
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

