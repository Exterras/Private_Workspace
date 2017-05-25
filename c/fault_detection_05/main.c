#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 전류 관련 정의
#define CUR_NUM 3
#define TXT_LEN 10

// 고장으로 판별할 수 있는 전류 급상승 갯수 정의
#define A_FAULT_CNT 10
#define B_FAULT_CNT 10
#define C_FAULT_CNT 10

// 고장으로 판별할 수 있는 전류 급상승 비율 정의
#define A_INC_PER 10.0
#define B_INC_PER 10.0
#define C_INC_PER 10.0

// 전류 배열 번호 정의
#define A_ARR_NUM 0
#define B_ARR_NUM 1
#define C_ARR_NUM 2

// 위상 배열 번호 정의 (0, 45, 90)
#define DEG_ZERO 0
#define DEG_HALF 1
#define DEG_ANGLE 2

// 기존의 고장분류 방법
#define NORMAL 0
#define FAULT_A 10
#define FAULT_B 11
#define FAULT_C 12

// 퍼지를 이용한 방법
#define INCREASE_HIGHER 10
#define SLIGHTLY_HIGHER 11
#define HIGH 12
#define VERY_HIGH 13

// 퍼지 비율 정의
#define PERCENT 100
#define AVGRANGE 0.5
#define LOWZERO 0.5
#define HIGHZERO 1.0

typedef struct faultChkValue {
   char *curName;
   int curLen;
   int faultChkTimes;
   double incPercent;
   int cnt;
} chk;

// double minFault = 0.2;
// Ver 4.0에서는 이 부분을 fuzzy c 코드와 결합시키기

// 정의 : 각 위상의 최대 전류값
// 20170410 4.0 version 부터 이 값을 주목하자
// 각 위상의 최대 전류값을 저장하여 3상의 값과 비교하여 가장 작은 값으로 고장판별을 할 기준으로 제공
int fuzzyFault[CUR_NUM];
double highCur;

void fault_detection(int _a, int _b, int _c);

// 각 전류별로 고장판별에 대한 함수를 만들고 오류가 발생시 해당 코드를 내보낸다.
int fault_A(int _faultChkTimes, double _incPercent);
int fault_B(int _faultChkTimes, double _incPercent);
int fault_C(int _faultChkTimes, double _incPercent);

bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent);

int file_open(char* _fileName);
double* file_save(char* _fileName);
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double* _curData);
int open_HigherFromMinFault(double *_curData, int _arrLen, double _minFault);
double* save_HigherFromMinFault(char *_data, int _arrLen, double _minFault);

int fuzzyOn(char *_curName, double *_num, int _numLength, int _degree, double _avgRate, double _num_LowZero, double _num_HighZero);
void fuzzyPrint(char* _str, double* _arrFuzzyValue, int _numLength, int _line); // fuzzy print function
void fault_detection_inFuzzy(int _a, int _b, int _c);

int main()
{
    int faultCnt[CUR_NUM] = {A_FAULT_CNT, B_FAULT_CNT, C_FAULT_CNT}; // 전류값이 해당 갯수 이상 급상승 시 고장이라고 판별해주는 기준,  A->B->C 순서
    double incPercent[CUR_NUM] = {A_INC_PER, B_INC_PER, C_INC_PER}; // 다음 전류값이 일정 비율 이상 급상승 시 고장이라고 판별해주는 기준,  A->B->C 순서

    // 각 위상값들을 모아 전류의 고장을 판별하는 함수
    // side effect 방지 코드, 함수안에 함수중첩을 가능한 피하자, 순서가 반대로 되는 것을 막아줌
    int fault_code[CUR_NUM] = { fault_A(faultCnt[A_ARR_NUM], incPercent[A_ARR_NUM]),
                                fault_B(faultCnt[B_ARR_NUM], incPercent[B_ARR_NUM]),
                                fault_C(faultCnt[C_ARR_NUM], incPercent[C_ARR_NUM])};

    // 실행 함수 (윗 : 각 상의 결과를 퍼지화하여 위험도를 알려줌, 아래: 최종적으로 어느 결과를 출력할 것이지를 알려줌)
    fault_detection_inFuzzy(fuzzyFault[A_ARR_NUM], fuzzyFault[B_ARR_NUM], fuzzyFault[C_ARR_NUM]);
    fault_detection(fault_code[A_ARR_NUM], fault_code[B_ARR_NUM], fault_code[C_ARR_NUM]);

    return 0;
}

// 각각의 전류의 고장을 따져서 최종 고장을 판단하는 함수
void fault_detection(int _a, int _b, int _c) {

    // 3상의 전류를 파악하여 고장 여부를 판별하기 위해 고장코드를 합산한다.
    // 고장코드 => A 고장 : 10, B 고장 : 11, C 고장 : 12, 정상 : 0
    int result  = _a + _b + _c;

    // 고장 코드를 출력하는 문이다. 0x is nothing.. just look..
    printf("Fault Code : 0x%d, ", result);

    // 전에서 입력된 고장코드를 통하여 제어문을 사용하여 고장을 판별한다.
    switch(result){
        case 0:
            printf("Normal");
        break;
        case FAULT_A:
            printf("A 지락");
        break;
        case FAULT_B:
            printf("B 지락");
        break;
        case FAULT_C:
            printf("C 지락");
        break;
        case (FAULT_A+FAULT_B):
            printf("AB 단락");
        break;
        case (FAULT_A+FAULT_C):
            printf("AC 단락");
        break;
        case (FAULT_B+FAULT_C):
            printf("BC 단락");
        break;
        case (FAULT_A+FAULT_B+FAULT_C):
            printf("3상 ABC 단락");
        break;
        default:
            printf("알 수 없음");
        break;
    }

    printf("\n"); // carriage return
}

// 각각의 상의 퍼지결과를 매개변수로 받아서 두 개 이상의 상의 퍼지화를 나타낸 함수
void fault_detection_inFuzzy(int _a, int _b, int _c){

    // 각 상의 퍼지결과를 별도의 변수로 만들어 저장함
    int a = _a;
    int b = _b;
    int c = _c;
    int ab = a+b;
    int bc = b+c;
    int ac = a+c;
    int abc = a+b+c;

    // 퍼지 알림코드
    char* errorArr[] = {"Increasing Higher", "Slightly Higher", "is High", "is Very High"};

    // 2개의 상의 결과가 일정 위험수준 사이에 있는다면
    // 그 결과의 십의 자리수를 빼고 상의 갯수만큼 나눗셈을 한다.
    // 그 수를 다시 상의 결과변수에 넣어 해당하는 퍼지 알림코드를 제공한다.
    if (ab >= (INCREASE_HIGHER*2) && ab <= (VERY_HIGH*2)){
        ab = (ab-20) / 2;
        printf("Current AB's Danger %s", errorArr[ab]);
    } else {
        printf("Current AB's Danger is Not Detected");
    } printf("\n");

    if (bc >= (INCREASE_HIGHER*2) && bc <= (VERY_HIGH*2)){
        bc = (bc-20) / 2;
        printf("Current BC's Danger %s", errorArr[bc]);
    } else {
        printf("Current BC's Danger is Not Detected");
    } printf("\n");

    if (ac >= (INCREASE_HIGHER*2) && ac <= (VERY_HIGH*2)){
        ac = (ac-20) / 2;
        printf("Current AC's Danger %s", errorArr[ac]);
    } else {
        printf("Current AC's Danger is Not Detected");
    } printf("\n");

    if (abc >= (INCREASE_HIGHER*3) && abc <= (VERY_HIGH*3)){
        abc = (abc-30) / 3;
        printf("Current ABC's Danger %s", errorArr[abc]);
    } else {
        printf("Current ABC's Danger is Not Detected");
    } printf("\n");

    printf("\n");
}

// 각 위상값들을 모아 전류의 고장을 판별하는 함수
// 퍼지 넣을 부분 fault_A, fault_B, fault_C
int fault_A(int _faultChkTimes, double _incPercent){
    bool flag = false; // 고장 여부를 판단할 플래그 설정
    int fault = NORMAL;

    // 20170410 added
    double minFault = 0.0;
    double cur_A_MAX[CUR_NUM]; // 각 위상의 최대 전류값을 저장할 배열 설정

    // 전류에 대한 구조체 정보와 실제 전류 파일
    chk cur_A[CUR_NUM];
    char cur_A_txt[CUR_NUM][TXT_LEN] = {"A_0.txt", "A_45.txt", "A_90.txt"};

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_A[i], cur_A_txt[i], file_open(cur_A_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 추가
        /* fault_check()에서 highCur는 특정 위상 전류값 중 가장 높은 값이다.
        *  특정 전류의 모든 값을 받아들여야 하기 때문에
        *  fault_check()가 실행될 때마다 그 값을 cur_A_MAX배열에 넣는다.
        *  fault_check()는 input_data()를 실행할 때마다 1번 실행 된다.
        */
        cur_A_MAX[i] = highCur;
        // printf("%lf ", cur_A_MAX[i]); // test

        // 처음 값은 무조건 최소값으로 지정하고
        // 두 번째 값부터 비교하는 방식으로 제작
        if(i == 0){
            minFault = cur_A_MAX[i];
        } else {
            if(cur_A_MAX[i] < minFault){
                minFault = cur_A_MAX[i];
            }
        }
        // input_data의 값이 true, 고장이다 라고 하면 고장코드를 리턴한다
        if (flag){
            fault = FAULT_A;
        }
    }

    // 각 위상값별로 최소 고장값의 갯수를 구하는 구문, 0도과 45도는
    // 각 위상값별로 최소 고장값의 갯수의 합을 구하여 다음 구문에 활용한다.
    int faultDataCnt = 0;
    int faultDataCnt_0 = open_HigherFromMinFault(file_save(cur_A_txt[DEG_ZERO]), file_open(cur_A_txt[DEG_ZERO]), minFault);
    int faultDataCnt_45 = open_HigherFromMinFault(file_save(cur_A_txt[DEG_HALF]), file_open(cur_A_txt[DEG_HALF]), minFault);
    for(i=0; i<CUR_NUM; i++){
        faultDataCnt += open_HigherFromMinFault(file_save(cur_A_txt[i]), file_open(cur_A_txt[i]), minFault);
    }

    // 각 위상값별로 최소 고장값을 저장하는 구문,
    double *faultDataArr_0 = save_HigherFromMinFault(cur_A_txt[DEG_ZERO], file_open(cur_A_txt[DEG_ZERO]), minFault);
    double *faultDataArr_45 = save_HigherFromMinFault(cur_A_txt[DEG_HALF], file_open(cur_A_txt[DEG_HALF]), minFault);
    double *faultDataArr_90 = save_HigherFromMinFault(cur_A_txt[DEG_ANGLE], file_open(cur_A_txt[DEG_ANGLE]), minFault);

    // 각 위상값의 최소 고장값들을 모아서 각 상(전류)의 고장값으로 재배치
    // 앞서 만든 각 위상값별로 최소 고장값의 갯수의 합만큼 배열을 생성해 이것을 포인트 변수로 정의하였다.
    double *faultDataArr = (double*)malloc(sizeof(double)*faultDataCnt);

    // 임시변수
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;

    // faultDataArr_0, faultDataArr_45, faultDataArr_90 포인터변수를 하나의 포인터변수(faultDataArr)로 합치는 과정이다.
    // 이 합친 데이터를 바탕으로 자료의 퍼지화를 제작한다.
    for(i=0; i<faultDataCnt; i++){
        if(i < faultDataCnt_0){
            faultDataArr[i] = faultDataArr_0[t1];
            t1++;
        } else if(i >= faultDataCnt_0 && i < (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_45[t2];
            t2++;
        } else if(i >= (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_90[t3];
            t3++;;
        }
    }
    /* // test
    for(i=0; i<faultDataCnt; i++){
        printf("%.10lf\n", faultDataArr[i]);
    }
    */

    // 전류이름, 전류데이터, 전류데이터의 갯수, 퍼지눈금(백분율), 평균집단 시작과 끝을 지정해줄 비율 (Low 와 High 정도로 각각 시작과 끝을 정한다), Low0.0의 데이터, HIGH0.0의 데이터
    // 퍼지화한 함수에서 퍼지코드를 fuzzyFault 배열변수에 저장한다.
    fuzzyFault[0] = fuzzyOn("Current A", faultDataArr, faultDataCnt, PERCENT, AVGRANGE, LOWZERO, HIGHZERO);

    // 자신의 전류에서 고장이 났는지 않났는지 확인해주는 장치이다. 종래의 방법으로 실행된다.
    return fault;

    // fault_B, C는 A와 동일한 구조로 가짐
}

int fault_B(int _faultChkTimes, double _incPercent){
    bool flag = false;
    int fault = NORMAL;

    chk cur_B[CUR_NUM];
    char cur_B_txt[CUR_NUM][TXT_LEN] = {"B_0.txt", "B_45.txt", "B_90.txt"};

    // 20170410 added
    double minFault = 0.0;
    double cur_B_MAX[CUR_NUM]; // 각 위상의 최대 전류값을 저장할 배열 설정
    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_B[i], cur_B_txt[i], file_open(cur_B_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 추가
        cur_B_MAX[i] = highCur;
        // printf("%lf ", cur_B_MAX[i]); // test
        if(i == 0){
            minFault = cur_B_MAX[i];
        } else {
            if(cur_B_MAX[i] < minFault){
                minFault = cur_B_MAX[i];
            }
        }

        if (flag){
            fault = FAULT_B;
        }
    }

    int faultDataCnt = 0;
    int faultDataCnt_0 = open_HigherFromMinFault(file_save(cur_B_txt[DEG_ZERO]), file_open(cur_B_txt[DEG_ZERO]), minFault);
    int faultDataCnt_45 = open_HigherFromMinFault(file_save(cur_B_txt[DEG_HALF]), file_open(cur_B_txt[DEG_HALF]), minFault);
    for(i=0; i<CUR_NUM; i++){
        faultDataCnt += open_HigherFromMinFault(file_save(cur_B_txt[i]), file_open(cur_B_txt[i]), minFault);
    }

    double *faultDataArr_0 = save_HigherFromMinFault(cur_B_txt[DEG_ZERO], file_open(cur_B_txt[DEG_ZERO]), minFault);
    double *faultDataArr_45 = save_HigherFromMinFault(cur_B_txt[DEG_HALF], file_open(cur_B_txt[DEG_HALF]), minFault);
    double *faultDataArr_90 = save_HigherFromMinFault(cur_B_txt[DEG_ANGLE], file_open(cur_B_txt[DEG_ANGLE]), minFault);

    double *faultDataArr = (double*)malloc(sizeof(double)*faultDataCnt);
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    for(i=0; i<faultDataCnt; i++){
        if(i < faultDataCnt_0){
            faultDataArr[i] = faultDataArr_0[t1];
            t1++;
        } else if(i >= faultDataCnt_0 && i < (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_45[t2];
            t2++;
        } else if(i >= (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_90[t3];
            t3++;;
        }
    }
    fuzzyFault[1] = fuzzyOn("Current B", faultDataArr, faultDataCnt, PERCENT, AVGRANGE, LOWZERO, HIGHZERO);
    // minFaultArr[1] = minFault; // minFault 외부로 빼내기
    return fault;
}

int fault_C(int _faultChkTimes, double _incPercent){
    bool flag = false;
    int fault = NORMAL;

    chk cur_C[CUR_NUM];
    char cur_C_txt[CUR_NUM][TXT_LEN] = {"C_0.txt", "C_45.txt", "C_90.txt"};

    // 20170410 added
    double minFault = 0.0;
    double cur_C_MAX[CUR_NUM]; // 각 위상의 최대 전류값을 저장할 배열 설정

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_C[i], cur_C_txt[i], file_open(cur_C_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 추가
        cur_C_MAX[i] = highCur;
        // printf("%lf ", cur_C_MAX[i]); // test
        if(i == 0){
            minFault = cur_C_MAX[i];
        } else {
            if(cur_C_MAX[i] < minFault){
                minFault = cur_C_MAX[i];
            }
        }

        if (flag){
            fault = FAULT_C;
        }
    }

    int faultDataCnt = 0;
    int faultDataCnt_0 = open_HigherFromMinFault(file_save(cur_C_txt[DEG_ZERO]), file_open(cur_C_txt[DEG_ZERO]), minFault);
    int faultDataCnt_45 = open_HigherFromMinFault(file_save(cur_C_txt[DEG_HALF]), file_open(cur_C_txt[DEG_HALF]), minFault);
    for(i=0; i<CUR_NUM; i++){
        faultDataCnt += open_HigherFromMinFault(file_save(cur_C_txt[i]), file_open(cur_C_txt[i]), minFault);
    }

    double *faultDataArr_0 = save_HigherFromMinFault(cur_C_txt[DEG_ZERO], file_open(cur_C_txt[DEG_ZERO]), minFault);
    double *faultDataArr_45 = save_HigherFromMinFault(cur_C_txt[DEG_HALF], file_open(cur_C_txt[DEG_HALF]), minFault);
    double *faultDataArr_90 = save_HigherFromMinFault(cur_C_txt[DEG_ANGLE], file_open(cur_C_txt[DEG_ANGLE]), minFault);

    double *faultDataArr = (double*)malloc(sizeof(double)*faultDataCnt);
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    for(i=0; i<faultDataCnt; i++){
        if(i < faultDataCnt_0){
            faultDataArr[i] = faultDataArr_0[t1];
            t1++;
        } else if(i >= faultDataCnt_0 && i < (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_45[t2];
            t2++;
        } else if(i >= (faultDataCnt_0+faultDataCnt_45) ){
            faultDataArr[i] = faultDataArr_90[t3];
            t3++;;
        }
    }
    fuzzyFault[2] = fuzzyOn("Current C", faultDataArr, faultDataCnt, PERCENT, AVGRANGE, LOWZERO, HIGHZERO);
    return fault;
}

// 특정 위상값의 고장을 판별하는 함수, 전류 정보를 구조체로 만듬
bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent) {
    // 고장을 판별하는 플래그 설정
    bool flag = false;

   _current.curName = _data;
   _current.curLen = _curLen;
   _current.faultChkTimes = _faultChkTimes;
   _current.incPercent = _incPercent;
   _current.cnt = fault_check(_current.curLen, _current.faultChkTimes, _current.incPercent, file_save(_current.curName));

   // printf("%s -> ", _data); // test
   if (_current.cnt >= _current.faultChkTimes) {
      // printf("cnt : %d, fault\n", _current.cnt);
      flag = true;
   } else {
      // printf("cnt : %d, normal\n", _current.cnt);
   }
   return flag;
}

// 파일을 열어주는 함수
int file_open(char *_fileName){
    FILE *fp;
    int cnt = 0;
    double data = 0.0;

    fp = fopen(_fileName, "r");

    // 파일을 읽어오지 못했다면 "fail" 이라는 메시지 출력
    if(fp == NULL){ printf("fail"); }

    // 파일을 열어 파일이 들어있는 갯수를 확인함
    while(fscanf(fp, "%lf", &data)!= EOF){
        // printf("%.10lf\n", data);
        cnt++;
    }

    // 파일이 들어있는 갯수를 리턴함
    return cnt;
}

// 파일을 저장하는 함수
double* file_save(char *_fileName){
    FILE *fp;
    int i = 0;
    int cnt = 0;
    double data = 0.0;

    // 파일을 저장하기 위해 앞선 함수를 호출하여 그 리턴값을 받아들임
    cnt = file_open(_fileName);

    // 파일의 갯수만큼 동적 할당 배열(curData)을 만든다. 그리고 그 값에 파일을 저장한다.
    double *curData = (double*)malloc(sizeof(double)*cnt);

    fp = fopen(_fileName, "r");
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
        //printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);

    // 저장된 파일의 포인터를 리턴한다.
    return curData;
}

// minFault보다 큰 전류값들의 갯수를 알려주는 함수, 반복횟수 : cntLen * CUR_NUM (101 * 3)
int open_HigherFromMinFault(double *_curData, int _arrLen, double _minFault){
    int i, cnt = 0;
    int arrLen = _arrLen;
    double minFault = _minFault;
    double *curData = _curData;

    for(i=0; i<arrLen; i++){
        if(minFault <= curData[i]){
            cnt++;
        }
    }
    return cnt;
}

// minFault보다 큰 전류값들을 저장하는 함수, 반복횟수 : cntLen * CUR_NUM (101 * 3)
// 저장된 배열의 포인터를 리턴한다. 리턴되는 배열 값들은 각 전류들의 고장범위를 알려준다.
double* save_HigherFromMinFault(char *_data, int _arrLen, double _minFault){
    int i, j = 0;
    int arrLen = _arrLen;
    double minFault = _minFault;
    double *curData = file_save(_data);

    int cnt = open_HigherFromMinFault(curData, arrLen, minFault);
    double *faultDataArr = (double*)malloc(sizeof(double)*cnt);

    for(i=0; i<arrLen; i++){
        if(minFault <= curData[i]){
            faultDataArr[j] = curData[i];
            j++;
        }
    }
    /*// test
    for(i=0; i<cnt; i++){
        printf("%.10lf\n", faultDataArr[i]);
    }
    */
    return faultDataArr;
}

// 특정 위상값이 급상승시 상승된 갯수를 알려주는 함수
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double* _curData){
    int i, cnt = 0;
    int cntLen = _cnt;

    double *curData = _curData; // para. file data to this func. data
    double transPer = ((_incPercent+100)/100); // percentage of rapid change current
    // printf("%lf\n", transPer); // test

    // 전의 자료와 비교하여 일정 비율(transPer) 이상보다 클 경우 특정 카운트(cnt)를 증가한다.
    // 2017.03.29 출력문을 하나로 합쳐보자.
    // 2017.03.29 tempCur = curData[0]; temp 를 삭제하였다.
    // 2017.03.29 tempCur -> highCur

    highCur = curData[0]; // initiation of highest current
    for(i=0; i<cntLen; i++){
        if (i < (cntLen-1)){
        // 다음에 이어질 코드는 비교 시 다음 전류와 이전의 전류를 비교하기 때문에 "데이터 전체 길이-1" 만큼의 조건에서만 실행되게 하였다.
            if(curData[i+1] > (curData[i] * transPer)){
                cnt++; // fault check
                // printf("%.10lf *\n", curData[i+1]); // data print test,
                // '*' means rapidly change current as compared with previous current
            } else {
                // printf("%.10lf\n", curData[i+1]); // data print test
            }

            if(curData[i+1] > curData[i] && curData[i+1] > highCur){
                highCur = curData[i+1];
                // 다음 전류와 이전 전류를 비교하여 큰 값에 highCur를 저장한다.
            }
        }
    }
    return cnt;
}

int fuzzyOn(char *_curName, double *_num, int _numLength, int _degree, double _avgRate, double _num_LowZero, double _num_HighZero){
// function of bubble sort
    // general variables
    char *curName = _curName;
    int i, j = 0; // bubble sort and iteration variables
    int errorCode = 0; // normal:0, I.High:10, S.High:11, High:12, Very High:13
    double temp = 0.0;
    double *num = _num; // array parameter to pointer variable
    double sum_Entire = 0; // array's sum
    double avg_Entire = 0.0; // array's avg
    double avgRate = _avgRate; // low and high rate = average's start and end point

    // data variables
    int numLength = _numLength; // array's length

    // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 변수는 쓰여지지 않는다.
    // int num_LowLast = 0; // low last in an array,

    double num_High; // array highest number, high 1.0's number
    double num_Low; // array lowest number, low 1.0's number
    double num_HighZero = _num_HighZero; // high 0.0's number
    double num_LowZero = _num_LowZero; // // low 0.0's number

    double num_FuzzyAvgInLow = 0.0; // avg 0.0's number -> 1.0
    double num_FuzzyAvgInHigh = 0.0; // 1.0 -> avg 0.0's number// Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 변수는 쓰여지지 않는다.
    double avg_FuzzyAvg = 0.0; // avg 1.0's number

    // fuzzy measurement variables
    int degree = _degree;
    double fuzzyLow = 0.0; // low fuzzy variable
    double fuzzyHigh = 0.0; // high fuzzy variable
    double fuzzyLowToAvg = 0.0; // avg-up fuzzy variable
    double fuzzyAvgToHigh = 0.0; // avg-down fuzzy variable
    double fuzzy_AvgInLow = avgRate;
    double fuzzy_AvgInHigh = avgRate;

    // fuzzy array variables
    double arr_FuzzyLow[numLength];
    double arr_FuzzyHigh[numLength];
    double arr_FuzzyLowToAvg[numLength];
    double arr_FuzzyAvgToHigh[numLength];

    /*
    // before bubble sort, initialize value
    printf("initialize value :\t");
    for(i = 0; i < numLength; i++){
        printf("%d ",num[i]);
    }
    printf("\n");
    */


    /* ----- bubble sort, maxvalue, minvalue, avgvalue -----*/

    // highest, lowest value
    num_High = num[0];
    num_Low = num[0];
    for(i = 0; i < numLength; i++){
        if(num[i] > num_High){
            num_High = num[i];
        }
        if(num[i] < num_Low){
            num_Low = num[i];
        }
    }

    // bubble sort
    for (i = 0; i < numLength; i++) {
        for (j = 0; j < numLength - 1; j++) {
            if (num[j] > num[j+1]) {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
            }
        }
    }

    /*
    // after bubble sort (Ascending)
    printf("after B.S. (Asc.):\t");
    for(i = 0; i < numLength; i++){
        printf("%d ",num[i]);
    }
    printf("\n"); // carriage return

    // after bubble sort (Descending)
    printf("after B.S. (Desc.):\t");
    for(i = numLength-1 ; i >= 0; i--){
        printf("%d ",num[i]);
    }
    printf("\n"); // carriage return
    */

    // num[]'s sum and average
    for(i = 0; i < numLength; i++){
        sum_Entire += num[i];
    } // iteration of number array adding


    avg_Entire = (double)sum_Entire / (double)numLength; // number array average method

    /* ----- calculation of fuzzy ----- */

   // low fuzzy 중 데이터가 가장 큰 변수를 골라내는 과정,
   // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 과정은 의미가 없다.
   // for (i = 0; i < numLength; i++) {
   //     if (num[i] < avg_Entire) {
   //         num_LowLast = num[i];
   //     }
   // }

    // 사용자가 설정한 degree 나누기 각 소속 집단별로 num_FuzzyAvgInLow최대값과 최소값를 구하여 그 차액 -> 전체 집단에서 한 눈금이 차지하는 비율
   // fuzzyLow = (double)degree / (double)(num_LowLast - num_Low); // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 과정은 의미가 없다.
    fuzzyLow = (double)degree / (double)(num_LowZero - num_Low);
    fuzzyHigh = (double)degree / (double)(num_High - num_HighZero);

    // num_FuzzyAvgInLow = (double)num_LowLast - ((fuzzy_AvgInLow * degree) / fuzzyLow); // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 과정은 의미가 없다.
    num_FuzzyAvgInLow = (double)num_LowZero - ((fuzzy_AvgInLow * degree) / fuzzyLow);
    // Low 집단 중 Average 집단에 소속될 수 있는 최소한의 데이터
    // low 집단 중 가장 큰 데이터  - (low 집단 중 평균으로 속할 수 있는 소속도 * degree) / low 집단전체 한 눈금이 차지하는 비율

    num_FuzzyAvgInHigh = ((fuzzy_AvgInHigh * degree) / fuzzyHigh) + (double)num_HighZero;
    // High 집단 중 Average 집단에 소속될 수 있는 최대한의 데이터 ==
    // (high 집단 중 평균으로 속할 수 있는 소속도 * degree) / low 집단에서 한 눈금이 차지하는 비율 + 큰 데이터를 판별하는 기준 데이터

    avg_FuzzyAvg = (num_FuzzyAvgInHigh + num_FuzzyAvgInLow) / 2.0;
    fuzzyLowToAvg = (double)degree / (avg_FuzzyAvg - num_FuzzyAvgInLow);
    fuzzyAvgToHigh = (double)degree / (num_FuzzyAvgInHigh - avg_FuzzyAvg);

    // 각 집단별 fuzzy 구하기
    for (i = 0; i < numLength; i++) {
        // 각 집단들의 퍼지 논리 (0~1 사이의 실수값) = (눈금자 * (최대범위 - 최소범위)) / degree
        // Fuzzy 값의 범위 = 0.0 ~ 1.0
        // arr_FuzzyLow[i] = (fuzzyLow * (double)(num_LowLast - num[i])) / (double)degree;
        // 바로 앞 줄의 과정은 Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 과정은 의미가 없다.
        arr_FuzzyLow[i] = (fuzzyLow * (double)(num_LowZero - num[i])) / (double)degree;
        arr_FuzzyHigh[i] = (fuzzyHigh * (double)(num[i] - num_HighZero)) / (double)degree;
        arr_FuzzyLowToAvg[i] = (fuzzyLowToAvg * (double)(num[i] - num_FuzzyAvgInLow)) / (double)degree;
        arr_FuzzyAvgToHigh[i] = (fuzzyAvgToHigh * (double)(num_FuzzyAvgInHigh - num[i])) / (double)degree;
    }

    // fuzzy print - low
    for (i = 0; i < numLength; i++) {
        if(arr_FuzzyLow[i] == 0.0){
            num_LowZero = num[i];
            break;
        }
    } // low fuzzy가 0.0인 데이터를 num_LowZero에 넣고 break

    // fuzzyPrint("Low Fuzzy :\t\t", arr_FuzzyLow, numLength, 1);

    // fuzzy print - high
    // fuzzyPrint("High Fuzzy :\t\t", arr_FuzzyHigh, numLength, 1);

    // fuzzy print - average
    // fuzzyPrint("LowToAvg Fuzzy :\t", arr_FuzzyLowToAvg, numLength, 2);
    // fuzzyPrint("AvgToHigh Fuzzy :\t", arr_FuzzyAvgToHigh, numLength, 2);

    // fuzzy decision

    // num_FuzzyAvgInLow : Low 집단 중 Average 집단에 소속될 수 있는 최소한의 데이터
    // num_FuzzyAvgInHigh :  High 집단 중 Average 집단에 소속될 수 있는 최대한의 데이터
    // num_HighZero : High 집단 fuzzy 0.0일때의 데이터
    // num_LowZero : Low 집단 fuzzy 0.0일때의 데이터
    // num_Low : 전체 집단 중 가장 작은 데이터

    // fuzzy point number print
    // printf("\n");

    printf("%s's sum :\t\t%.3lf\n", curName, sum_Entire);
    printf("%s's avg :\t\t%.5lf\n", curName, avg_Entire);

    printf("%s's low :\t\t%.10lf\n", curName, num_Low);
    printf("%s's avg 0.0 start: \t%.10lf\n", curName, num_FuzzyAvgInLow);
    printf("%s's low 0.0 :\t\t%.10lf\n", curName, num_LowZero);
    printf("%s's avg 1.0 :\t\t%.10lf\n", curName, avg_FuzzyAvg);
    printf("%s's high 0.0 :\t\t%.10lf\n", curName, num_HighZero);
    printf("%s's avg 0.0 end:\t%.10lf\n", curName, num_FuzzyAvgInHigh);
    printf("%s's high :\t\t%.10lf\n", curName, num_High);

    // printf("%s's fuzzy decision:\t", curName);
    if(avg_Entire >= num_HighZero){
        printf("%s's Danger is Very High\n", curName);
        errorCode = VERY_HIGH;
    } else if(avg_Entire >= avg_FuzzyAvg && avg_Entire < num_HighZero){
        printf("%s's Danger is High\n", curName);
        errorCode = HIGH;
    } else if(avg_Entire >= num_LowZero && avg_Entire < avg_FuzzyAvg){
        printf("%s's Danger Slightly Higher\n", curName);
        errorCode = SLIGHTLY_HIGHER;
    } else if(avg_Entire >= num_FuzzyAvgInLow && avg_Entire < num_LowZero){
        printf("%s's Danger Increasing Higher\n", curName);
        errorCode = INCREASE_HIGHER;
    } else {
        printf("%s's Danger is Not Detected\n", curName);
        errorCode = NORMAL;
    }

    printf("\n");

    return errorCode;

}

void fuzzyPrint(char* _str, double* _arrFuzzyValue, int _numLength, int _line){
    // fuzzy print function
    int i;

    printf("%s", _str);
    for(i = 0; i < _numLength; i++){
        if(_line == 1){
            if(_arrFuzzyValue[i] > 0.0){
                printf("%.2lf ", _arrFuzzyValue[i]);
            } else {
                printf("%.2lf ", 0.0);
            }
        } else {
            if(_arrFuzzyValue[i] > 0.0 && _arrFuzzyValue[i] < 1.0){
                printf("%.2lf ", _arrFuzzyValue[i]);
            } else if (_arrFuzzyValue[i] < 0.0){
                printf("%.2lf ", 0.0);
            } else if (_arrFuzzyValue[i] == 1.0){
                printf("%.2lf ", 1.0);
            } else {
                printf("VOID ");
            }
        }
    // printf("%.2lf ", arrFuzzyValue[i]);
    }
    printf("\n");
}
