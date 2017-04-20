#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BINNUM 5
#define MAXNUM 25
#define STARTNUM 1

// version control
void bingoVer01(void);
void bingoVer02(void);
void bingoVer03(void);
void bingoVer04(void);

typedef struct bingoVariable{
    int num;
} Bingo;

int main(void){
    bingoVer04();
    return 0;
}

// 1���� 25���� ����
void bingoVer01(void){
    int i, j;
    int bingoAry[BINNUM][BINNUM] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};

    // �迭 ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", bingoAry[i][j]);
        }
        printf("\n");
    }
}

// �ߺ� �̱���
void bingoVer02(void){
    int i, j;
    Bingo numArr[BINNUM][BINNUM];

    // �迭 (����) �Է� - �ߺ� �̱���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            numArr[i][j].num = (rand() % 25) + 1;
        }
    }

    // �迭 ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}

// �ߺ� ������
void bingoVer03(void){
    int i, j, k;
    Bingo numArr[BINNUM][BINNUM]; // ���� ����ü�� �迭
    srand(time(NULL)); // �Ź� �ٸ� �����Լ� ����?

    // �迭 (����) �Է� - �ߺ� ����?? ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){

        }

        for(k=0; k<BINNUM; k++){
            numArr[i][j].num = (rand() % MAXNUM) + STARTNUM;
        }
    }

    // �迭 ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}

// ���� - �ߺ� ����� �ٲ��.
void bingoVer04(void){
    // ��������
    int i, j, temp; // �ݺ��� ���� ����, temp = �ӽ� �迭 ���� ����
    int count = 1; // �ʱ� �迭 ���尪
    int ranArrNumX, ranArrNumY; // �迭�� ��ġ�� ����ȭ
    int bingoAry[BINNUM][BINNUM]; // �ʱ� �迭�� �����ϰ� ����ȭ�� �迭�� ������

    Bingo numArr[BINNUM][BINNUM]; // ���� ����ü�� �迭
    srand(time(NULL)); // �Ź� �ٸ� �����Լ� ����?

    // �ʱ� �迭 ����
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            bingoAry[i][j] = count;
            count++;
        }
    }

    // �ߺ� ����
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            ranArrNumX = (rand() % BINNUM);
            ranArrNumY = (rand() % BINNUM);

            temp = bingoAry[ranArrNumX][ranArrNumY];
            bingoAry[ranArrNumX][ranArrNumY] = bingoAry[i][j];
            bingoAry[i][j] = temp;
        }
    }

    // ���ŵ� ���ڸ� �ش� �迭�� ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            numArr[i][j].num = bingoAry[i][j];
        }
    }

    // �迭 ���
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}
