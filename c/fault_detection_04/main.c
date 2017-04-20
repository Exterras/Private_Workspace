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
// Ver 4.0������ �� �κ��� fuzzy c �ڵ�� ���ս�Ű��

// ���� : �� ������ �ִ� ������
// 20170410 4.0 version ���� �� ���� �ָ�����
// �� ������ �ִ� �������� �����Ͽ� 3���� ���� ���Ͽ� ���� ���� ������ �����Ǻ��� �� �������� ����
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
    // �� �������� �����Ǻ��� ���� �Լ��� ����� ������ �߻��� �ش� �ڵ带 ��������.
    // �����ڵ� => A ���� : 10, B ���� : 11, C ���� : 12, ���� : 0

    // �������� �ش� ���� �̻� �޻�� �� �����̶�� �Ǻ����ִ� ����,  A->B->C ����
    // ���� �������� ���� ���� �̻� �޻�� �� �����̶�� �Ǻ����ִ� ����,  A->B->C ����
    int faultCnt[CUR_NUM] = {10, 10, 10};
    double incPercent[CUR_NUM] = {10.0, 10.0, 10.0};

    // side effect ���� �ڵ�, �Լ��ȿ� �Լ���ø�� ������ ������, ������ �ݴ�� �Ǵ� ���� ������
    int fault_code[CUR_NUM] = {fault_A(faultCnt[0], incPercent[0]), fault_B(faultCnt[1], incPercent[1]), fault_C(faultCnt[2], incPercent[2])};

    // ���� �Լ�
    fault_detection(fault_code[0], fault_code[1], fault_code[2]);
    return 0;
}

// ������ ������ ������ ������ ���� ������ �Ǵ��ϴ� �Լ�
void fault_detection(int _a, int _b, int _c) {

    // 3���� ������ �ľ��Ͽ� ���� ���θ� �Ǻ��ϱ� ���� �����ڵ带 �ջ��Ѵ�.
    int result  = _a + _b + _c;

    // ���� �ڵ带 ����ϴ� ���̴�. 0x is nothing.. just look..
    printf("Fault Code : 0x%d, ", result);

    // ������ �Էµ� �����ڵ带 ���Ͽ� ����� ����Ͽ� ������ �Ǻ��Ѵ�.
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
// �� ���󰪵��� ��� ������ ������ �Ǻ��ϴ� �Լ�
int fault_A(int _faultChkTimes, double _incPercent){
    bool flag = false; // ���� ���θ� �Ǵ��� �÷��� ����
    int fault = NORMAL;

    // 20170410 added
    double minFault = 0.0;
    double cur_A_MAX[CUR_NUM]; // �� ������ �ִ� �������� ������ �迭 ����

    // ������ ���� ����ü ������ ���� ���� ����
    chk cur_A[CUR_NUM];
    char cur_A_txt[CUR_NUM][TXT_LEN] = {"A_0.txt", "A_45.txt", "A_90.txt"};

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_A[i], cur_A_txt[i], file_open(cur_A_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 �߰�
        /* fault_check()���� highCur�� Ư�� ���� ������ �� ���� ���� ���̴�.
        *  Ư�� ������ ��� ���� �޾Ƶ鿩�� �ϱ� ������
        *  fault_check()�� ����� ������ �� ���� cur_A_MAX�迭�� �ִ´�.
        *  fault_check()�� input_data()�� ������ ������ 1�� ���� �ȴ�.
        */
        cur_A_MAX[i] = highCur;
        // printf("%lf ", cur_A_MAX[i]); // test

        // ó�� ���� ������ �ּҰ����� �����ϰ�
        // �� ��° ������ ���ϴ� ������� ����
        if(i == 0){
            minFault = cur_A_MAX[i];
        } else {
            if(cur_A_MAX[i] < minFault){
                minFault = cur_A_MAX[i];
            }
        }
        // input_data�� ���� true, �����̴� ��� �ϸ� �����ڵ带 �����Ѵ�
        if (flag){
            fault = FAULT_A;
        }
    }
    return fault;

    // fault_B, C�� A�� ������ ������ ����
}

int fault_B(int _faultChkTimes, double _incPercent){
    bool flag = false;
    int fault = NORMAL;

    chk cur_B[CUR_NUM];
    char cur_B_txt[CUR_NUM][TXT_LEN] = {"B_0.txt", "B_45.txt", "B_90.txt"};

    // 20170410 added
    double minFault = 0.0;
    double cur_B_MAX[CUR_NUM]; // �� ������ �ִ� �������� ������ �迭 ����

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_B[i], cur_B_txt[i], file_open(cur_B_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 �߰�
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
    double cur_C_MAX[CUR_NUM]; // �� ������ �ִ� �������� ������ �迭 ����

    int i;
    for(i=0; i<CUR_NUM; i++){
        flag = input_data(cur_C[i], cur_C_txt[i], file_open(cur_C_txt[i]), _faultChkTimes, _incPercent);

        // 20170410 �߰�
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
// Ư�� ������ ������ �Ǻ��ϴ� �Լ�, ���� ������ ����ü�� ����
bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent) {
    // ������ �Ǻ��ϴ� �÷��� ����
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

// Ư�� ������ �޻�½� ��µ� ������ �˷��ִ� �Լ�
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double* _curData){
    int i, cnt = 0;
    int cntLen = _cnt;

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
    return cnt;
}
