#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CUR_NUM 3
#define TXT_LEN 10

#define NORMAL 0
#define FAULT_A 10
#define FAULT_B 11
#define FAULT_C 12

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
double highCur = 0.0;


void fault_detection(int _a, int _b, int _c);
int fault_A(int _faultChkTimes, double _incPercent);
int fault_B(int _faultChkTimes, double _incPercent);
int fault_C(int _faultChkTimes, double _incPercent);
bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent);

int file_open(char* _fileName);
double* file_save(char* _fileName);
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double* _curData);

int main()
{
    // int _faultChkTimes, double _incPercent
    // 각 전류별로 고장판별에 대한 함수를 만들고 오류가 발생시 해당 코드를 내보낸다.
    // 고장코드 => A 고장 : 10, B 고장 : 11, C 고장 : 12, 정상 : 0

    // 전류값이 해당 갯수 이상 급상승 시 고장이라고 판별해주는 기준,  A->B->C 순서
    // 다음 전류값이 일정 비율 이상 급상승 시 고장이라고 판별해주는 기준,  A->B->C 순서
    int faultCnt[CUR_NUM] = {10, 10, 10};
    double incPercent[CUR_NUM] = {10.0, 10.0, 10.0};

    // side effect 방지 코드, 함수안에 함수중첩을 가능한 피하자, 순서가 반대로 되는 것을 막아줌
    int fault_code[CUR_NUM] = {fault_A(faultCnt[0], incPercent[0]), fault_B(faultCnt[1], incPercent[1]), fault_C(faultCnt[2], incPercent[2])};

    // 실행 함수
    fault_detection(fault_code[0], fault_code[1], fault_code[2]);
    return 0;
}

// 각각의 전류의 고장을 따져서 최종 고장을 판단하는 함수
void fault_detection(int _a, int _b, int _c) {

    // 3상의 전류를 파악하여 고장 여부를 판별하기 위해 고장코드를 합산한다.
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
}
// 각 위상값들을 모아 전류의 고장을 판별하는 함수
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
