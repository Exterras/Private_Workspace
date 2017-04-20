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

// ������ �����ִ� �Լ�
int file_open(char *_fileName){
    FILE *fp;
    int cnt = 0;
    double data = 0.0;

    fp = fopen(_fileName, "r");

    // ������ �о���� ���ߴٸ� "fail" �̶�� �޽��� ���
    if(fp == NULL){ printf("fail"); }

    // ������ ���� ������ ����ִ� ������ Ȯ����
    while(fscanf(fp, "%lf", &data)!= EOF){
        // printf("%.10lf\n", data);
        cnt++;
    }

    // ������ ����ִ� ������ ������
    return cnt;
}

// ������ �����ϴ� �Լ�
double* file_save(char *_fileName){
    FILE *fp;
    int i = 0;
    int cnt = 0;
    double data = 0.0;

    // ������ �����ϱ� ���� �ռ� �Լ��� ȣ���Ͽ� �� ���ϰ��� �޾Ƶ���
    cnt = file_open(_fileName);

    // ������ ������ŭ ���� �Ҵ� �迭(curData)�� �����. �׸��� �� ���� ������ �����Ѵ�.
    double *curData = (double*)malloc(sizeof(double)*cnt);

    fp = fopen(_fileName, "r");
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
        //printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);

    // ����� ������ �����͸� �����Ѵ�.
    return curData;
}

// ���� ������ ������ �Ǻ��ϴ� �Լ�
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double _minFault, double* _curData){
    int i, cnt = 0;
    int cntLen = _cnt;

    double highCur; // the most highest of this data (current)
    double minFault = _minFault; // the mininum of fault current
    double *curData = _curData; // para. file data to this func. data
    double transPer = ((_incPercent+100)/100); // percentage of rapid change current
    // printf("%lf\n", transPer); // test

    // ���� �ڷ�� ���Ͽ� ���� ����(transPer) �̻󺸴� Ŭ ��� Ư�� ī��Ʈ(cnt)�� �����Ѵ�.
    // 2017.03.29 ��¹��� �ϳ��� ���ĺ���.
    // 2017.03.29 tempCur = curData[0]; temp �� �����Ͽ���.
    // 2017.03.29 tempCur -> highCur

    highCur = curData[0]; // initiation of highest current
    for(i=0; i<cntLen; i++){
        if (i < (cntLen-1)){
        // ������ �̾��� �ڵ�� �� �� ���� ������ ������ ������ ���ϱ� ������ "������ ��ü ����-1" ��ŭ�� ���ǿ����� ����ǰ� �Ͽ���.
            if(curData[i+1] > (curData[i] * transPer)){
                cnt++; // fault check
                // printf("%.10lf *\n", curData[i+1]); // data print test,
                // '*' means rapidly change current as compared with previous current
            } else {
                // printf("%.10lf\n", curData[i+1]); // data print test
            }

            if(curData[i+1] > curData[i] && curData[i+1] > highCur){
                highCur = curData[i+1];
                // ���� ������ ���� ������ ���Ͽ� ū ���� highCur�� �����Ѵ�.
            }
        }
    }

    // Ư�� ī��Ʈ(cnt) �� ��������Ƚ��(�Ű���������)���� ���� ��� ������� �����ϴ� ����
    // 20170331 �� �κ��� �ܺη� ������ ����
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
            printf("A ����");
        break;
        case FAULT_B:
            printf("B ����");
        break;
        case FAULT_C:
            printf("C ����");
        break;
        case (FAULT_A+FAULT_B):
            printf("AB �ܶ�");
        break;
        case (FAULT_A+FAULT_C):
            printf("AC �ܶ�");
        break;
        case (FAULT_B+FAULT_C):
            printf("BC �ܶ�");
        break;
        case (FAULT_A+FAULT_B+FAULT_C):
            printf("3�� ABC �ܶ�");
        break;
        default:
            printf("�� �� ����");
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
    // ������ �Ǻ��ϴ� �÷��� ����
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
