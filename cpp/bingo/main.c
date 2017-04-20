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

// 1부터 25까지 찍어내기
void bingoVer01(void){
    int i, j;
    int bingoAry[BINNUM][BINNUM] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};

    // 배열 출력
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", bingoAry[i][j]);
        }
        printf("\n");
    }
}

// 중복 미구현
void bingoVer02(void){
    int i, j;
    Bingo numArr[BINNUM][BINNUM];

    // 배열 (랜덤) 입력 - 중복 미구현
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            numArr[i][j].num = (rand() % 25) + 1;
        }
    }

    // 배열 출력
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}

// 중복 실패작
void bingoVer03(void){
    int i, j, k;
    Bingo numArr[BINNUM][BINNUM]; // 빙고 구조체의 배열
    srand(time(NULL)); // 매번 다른 랜덤함수 제공?

    // 배열 (랜덤) 입력 - 중복 구현?? 어렵
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){

        }

        for(k=0; k<BINNUM; k++){
            numArr[i][j].num = (rand() % MAXNUM) + STARTNUM;
        }
    }

    // 배열 출력
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}

// 랜덤 - 중복 방식을 바꿨다.
void bingoVer04(void){
    // 지역변수
    int i, j, temp; // 반복문 전용 변수, temp = 임시 배열 저장 변수
    int count = 1; // 초기 배열 저장값
    int ranArrNumX, ranArrNumY; // 배열의 위치를 랜덤화
    int bingoAry[BINNUM][BINNUM]; // 초기 배열을 생성하고 랜덤화된 배열로 제작함

    Bingo numArr[BINNUM][BINNUM]; // 빙고 구조체의 배열
    srand(time(NULL)); // 매번 다른 랜덤함수 제공?

    // 초기 배열 만듬
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            bingoAry[i][j] = count;
            count++;
        }
    }

    // 중복 제거
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            ranArrNumX = (rand() % BINNUM);
            ranArrNumY = (rand() % BINNUM);

            temp = bingoAry[ranArrNumX][ranArrNumY];
            bingoAry[ranArrNumX][ranArrNumY] = bingoAry[i][j];
            bingoAry[i][j] = temp;
        }
    }

    // 제거된 숫자를 해당 배열에 출력
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            numArr[i][j].num = bingoAry[i][j];
        }
    }

    // 배열 출력
    for(i=0; i<BINNUM; i++){
        for(j=0; j<BINNUM; j++){
            printf("%d\t", numArr[i][j].num);
        }
        printf("\n");
    }
}
