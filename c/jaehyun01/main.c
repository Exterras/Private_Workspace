#include <stdio.h>

/*int main()
{
    // ���� ���� ���ڿ� ���� ������ �Է¹޴� ���� ����
    int cnt;
    int num;

    // �ȳ���
    printf("���� ���� ���ڿ� ���� ������ �����ÿ�\n");

    // �Էº�
    scanf("%d", &cnt);
    scanf("%d", &num);

    printf("\n");

    calcu(cnt, num);
    return 0;
}*/

int main(){
    char a = 0xff;

    printf("%x", a);

    return 0;
}

// ����ڷκ��� �Է¹��� �޾Ƽ� ó���ϴ� �Լ� (����, ���� ���� ����)
void calcu(int _cnt, int _num){

    // ���� ���� (�ݺ�ȹ��, �հ躯��, ���ڸ� �и��� �迭����, ���� ����)
    int i, sum = 0;
    int num[_cnt];
    int arrLength = sizeof(num) / sizeof(num[0]);

    // �Է¹��� ���ڸ� �и��ϴ� ����
    for(i = 0; i < arrLength; i++){
        if(i == 0){
            num[i] = _num % 10;
        } else {
            _num = _num / 10;
            num[i] = _num % 10;
        }
    }

    // �и��� ������ �ջ��ϴ� ����
    for(i = 0; i < arrLength; i++){
        sum += num[i];
    }

    // ��¹�
    printf("���� ��� : %d\n", sum);
}

