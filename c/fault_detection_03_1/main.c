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
}chk;

double minFault = 0.2;

int file_open(char* _fileName);
double* file_save(char* _fileName);
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double _minFault, double* _curData);
void fault_detection(void);
bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent);
void fault_handler(int _cnt, int _faultChkTimes);
void string_delete(char *_str, char _delStr);

int fault_detection_A(int _faultChkTimes, double _incPercent);
int fault_detection_B(int _faultChkTimes, double _incPercent);
int fault_detection_C(int _faultChkTimes, double _incPercent);

int main()
{
   fault_detection();
   return 0;
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

// 개별 전류의 고장을 판별하는 함수
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double _minFault, double* _curData){
    int i, cnt = 0;
    int cntLen = _cnt;

    double highCur; // the most highest of this data (current)
    double minFault = _minFault; // the mininum of fault current
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

    // 특정 카운트(cnt) 가 오류검출횟수(매개변수지정)보다 높을 경우 오류라고 인지하는 구문
    // 20170331 이 부분은 외부로 독립될 예정
    if(cnt >= _faultChkTimes && highCur >= minFault){
        // printf("cnt : %d, fault\n", cnt);
    } else {
        // printf("cnt : %d, normal\n", cnt);
    }

    return cnt;
}

void fault_detection(void) {

    // chk cur_A[CUR_NUM], cur_B[CUR_NUM], cur_C[CUR_NUM];
    // char cur_A_txt[CUR_NUM][TXT_LEN] = {"A_0.txt", "A_45.txt", "A_90.txt"};
    // char cur_B_txt[CUR_NUM][TXT_LEN] = {"B_0.txt", "B_45.txt", "B_90.txt"};
    // char cur_C_txt[CUR_NUM][TXT_LEN] = {"C_0.txt", "C_45.txt", "C_90.txt"};

    int a = fault_detection_A(10, 10);
    int b = fault_detection_B(10, 10);
    int c = fault_detection_C(10, 10);
    int result  = a + b + c;

    /*
    #define FAULT_A 10
    #define FAULT_B 11
    #define FAULT_C 12
    */

    // 0x is nothing.. just look..
    printf("Fault Code : 0x%d, ", result);

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

int fault_detection_A(int _faultChkTimes, double _incPercent){
    int fault = 0;
    bool flag = false;

    chk cur_A[CUR_NUM];
    char cur_A_txt[CUR_NUM][TXT_LEN] = {"A_0.txt", "A_45.txt", "A_90.txt"};

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_A[i], cur_A_txt[i], file_open(cur_A_txt[i]), _faultChkTimes, _incPercent);
        if (flag){
            fault = FAULT_A;
        }
    }
    return fault;
}

int fault_detection_B(int _faultChkTimes, double _incPercent){
    int fault = 0;
    bool flag = false;

    chk cur_B[CUR_NUM];
    char cur_B_txt[CUR_NUM][TXT_LEN] = {"B_0.txt", "B_45.txt", "B_90.txt"};

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_B[i], cur_B_txt[i], file_open(cur_B_txt[i]), _faultChkTimes, _incPercent);
        if (flag){
            fault = FAULT_B;
        }
    }
    return fault;
}

int fault_detection_C(int _faultChkTimes, double _incPercent){
    int fault = 0;
    bool flag = false;

    chk cur_C[CUR_NUM];
    char cur_C_txt[CUR_NUM][TXT_LEN] = {"C_0.txt", "C_45.txt", "C_90.txt"};

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_C[i], cur_C_txt[i], file_open(cur_C_txt[i]), _faultChkTimes, _incPercent);
        if (flag){
            fault = FAULT_C;
        }
    }
    return fault;
}

bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent) {
    // 고장을 판별하는 플래그 설정
    bool flag = false;

   _current.curName = _data;
   _current.curLen = _curLen;
   _current.faultChkTimes = _faultChkTimes;
   _current.incPercent = _incPercent;
   _current.cnt = fault_check(
      _current.curLen,
      _current.faultChkTimes,
      _current.incPercent,
      minFault,
      file_save(_current.curName));

   // printf("%s -> ", _data); // test
   // fault_handler(_current.cnt, _current.faultChkTimes); // deprecated
   if (_current.cnt >= _current.faultChkTimes) {
      // printf("cnt : %d, fault\n", _current.cnt); // test
      flag = true;
   }
   else {
      // printf("cnt : %d, normal\n", _current.cnt); // test
   }

   return flag;
}

// old function, inside input_data
void fault_handler(int _cnt, int _faultChkTimes) {
   if (_cnt >= _faultChkTimes) {
      printf("cnt : %d, fault\n", _cnt);
   }
   else {
      printf("cnt : %d, normal\n", _cnt);
   }
}

void string_delete(char *_str, char _delStr) {
   for (; *_str != '\0'; _str++) {
      if (*_str == _delStr) {
         strcpy(_str, _str + 1);
         _str--;
      }
   }
}
