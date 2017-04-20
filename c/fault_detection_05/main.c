#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CUR_NUM 3
#define TXT_LEN 10
#define FUZZY_DATALEN 10

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
double highCur;
double minFaultArr[CUR_NUM];

void fault_detection(int _a, int _b, int _c);
int fault_A(int _faultChkTimes, double _incPercent);
int fault_B(int _faultChkTimes, double _incPercent);
int fault_C(int _faultChkTimes, double _incPercent);
bool input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent);

int file_open(char* _fileName);
double* file_save(char* _fileName);
int fault_check(int _cnt, int _faultChkTimes, double _incPercent, double* _curData);
int open_HigherFromMinFault(double *_curData, int _arrLen, double _minFault);
double* save_HigherFromMinFault(char *_data, int _arrLen, double _minFault);

double* bubbleSortArr(int _numLength, double _num_High, double _num_Low, double *_num);
void fuzzyOn(double *_num, int _numLength, int _degree, double _avgRate, double _num_LowZero, double _num_HighZero);
void fuzzyPrint(char* _str, double* _arrFuzzyValue, int _numLength, int _line); // fuzzy print function

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

    // ���⼭ �� �������� �ּ� ���尪�� �������Ƿ� �� �κп� ������ ����
    // minFaultArr[0] = A, minFaultArr[1] = B, minFaultArr[2] = C;

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

    printf("\n"); // carriage return
}
// �� ���󰪵��� ��� ������ ������ �Ǻ��ϴ� �Լ�
// ���� ���� �κ� fault_A, fault_B, fault_C
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

    double *faultDataArr_0 = save_HigherFromMinFault(cur_A_txt[0], file_open(cur_A_txt[0]), minFault);
    double *faultDataArr_45 = save_HigherFromMinFault(cur_A_txt[1], file_open(cur_A_txt[1]), minFault);
    double *faultDataArr_90 = save_HigherFromMinFault(cur_A_txt[2], file_open(cur_A_txt[2]), minFault);

    // int _numLength = open_HigherFromMinFault()
    // int _num_High = int _num_Low = �迭[0]��° ������ �ʱ�ȭ
    int cnt_0 = open_HigherFromMinFault(file_save(cur_A_txt[0]), file_open(cur_A_txt[0]), minFault);
    int cnt_45 = open_HigherFromMinFault(file_save(cur_A_txt[1]), file_open(cur_A_txt[1]), minFault);
    int cnt_90 = open_HigherFromMinFault(file_save(cur_A_txt[2]), file_open(cur_A_txt[2]), minFault);

    faultDataArr_0 = bubbleSortArr(cnt_0, faultDataArr_0[0], faultDataArr_0[0], faultDataArr_0);
    faultDataArr_45 = bubbleSortArr(cnt_45, faultDataArr_45[0], faultDataArr_45[0], faultDataArr_45);
    faultDataArr_90 = bubbleSortArr(cnt_90, faultDataArr_90[0], faultDataArr_90[0], faultDataArr_90);

    minFaultArr[0] = minFault; // minFault �ܺη� ������
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
    minFaultArr[1] = minFault; // minFault �ܺη� ������

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
    minFaultArr[2] = minFault; // minFault �ܺη� ������

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
    free(curData);
    return curData;
}

// minFault���� ū ���������� ������ �˷��ִ� �Լ�, �ݺ�Ƚ�� : cntLen * CUR_NUM (101 * 3)
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

// minFault���� ū ���������� �����ϴ� �Լ�, �ݺ�Ƚ�� : cntLen * CUR_NUM (101 * 3)
// ����� �迭�� �����͸� �����Ѵ�. �� ������ �� �������� ����
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
    /* test
    for(i=0; i<cnt; i++){
        printf("%.10lf\n", faultDataArr[i]);
    }
    */
    free(faultDataArr);
    return faultDataArr;
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

// 20170419 5.0 �������� fuzzyOn�� ���� bubbleSort�� ������ �Լ��� ����
// �� ���� �ּ����������� ū ������ ���յ��� �����ϴ� ���� ���� ���̴�.
// int _numLength = open_HigherFromMinFault()
// int _num_High = int _num_Low = �迭[0]��° ������ �ʱ�ȭ
double* bubbleSortArr(int _numLength, double _num_High, double _num_Low, double *_num){
    int i, j = 0;
    int numLength = _numLength;
    double num_High = _num_High;
    double num_Low = _num_Low;

    double *num = _num;
    double temp = 0.0;

    // highest, lowest value
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

    // after bubble sort (Ascending)
    printf("after B.S. (Asc.):\t");
    for(i = 0; i < numLength; i++){
        printf("%.5lf ",num[i]);
    }
    printf("\n"); // carriage return

    // after bubble sort (Descending)
    //printf("after B.S. (Desc.):\t");
    //for(i = numLength-1 ; i >= 0; i--){
    //    printf("%.5lf ",num[i]);
  //  }
    printf("\n"); // carriage return

    return num;
}


// function of bubble sort
void fuzzyOn(double *_num, int _numLength, int _degree, double _avgRate, double _num_LowZero, double _num_HighZero){
    // general variables
    int i; // bubble sort and iteration variables
    double *num = _num; // array parameter to pointer variable
    double sum_Entire= 0; // array's sum
    double avg_Entire = 0.0; // array's avg
    double avgRate = _avgRate; // low and high rate = average's start and end point

    // data variables
    int numLength = _numLength; // array's length

    // Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �������� �ʴ´�.
    // int num_LowLast = 0; // low last in an array,

    double num_High; // array highest number, high 1.0's number
    double num_Low; // array lowest number, low 1.0's number
    double num_HighZero = _num_HighZero; // high 0.0's number
    double num_LowZero = _num_LowZero; // // low 0.0's number

    double num_FuzzyAvgInLow = 0.0; // avg 0.0's number -> 1.0
    double num_FuzzyAvgInHigh = 0.0; // 1.0 -> avg 0.0's number// Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �������� �ʴ´�.
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
    double arr_FuzzHigh[numLength];
    double arr_FuzzyLowToAvg[numLength];
    double arr_FuzzyAvgToHigh[numLength];

    // before bubble sort, initialize value
    printf("initialize value :\t");
    for(i = 0; i < numLength; i++){
        printf("%.5lf ",num[i]);
    }
    printf("\n");

    // high, low initiation and bubblesort function execution
    num_High = num_Low = num[0];
    num = bubbleSortArr(numLength, num_High, num_Low, num);

    // num[]'s sum and average
    for(i = 0; i < numLength; i++){
        sum_Entire += num[i];
    } // iteration of number array adding

    avg_Entire = (double)sum_Entire / (double)numLength; // number array average method



    /* ----- calculation of fuzzy ----- */

   // low fuzzy �� �����Ͱ� ���� ū ������ ��󳻴� ����,
   // Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �ǹ̰� ����.
   // for (i = 0; i < numLength; i++) {
   //     if (num[i] < avg_Entire) {
   //         num_LowLast = num[i];
   //     }
   // }

    // ����ڰ� ������ degree ������ �� �Ҽ� ���ܺ��� �ִ밪�� �ּҰ��� ���Ͽ� �� ���� -> ��ü ���ܿ��� �� ������ �����ϴ� ����
   // fuzzyLow = (double)degree / (double)(num_LowLast - num_Low); // Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �ǹ̰� ����.
    fuzzyLow = (double)degree / (double)(num_LowZero - num_Low);
    fuzzyHigh = (double)degree / (double)(num_High - num_HighZero);

    // num_FuzzyAvgInLow = (double)num_LowLast - ((fuzzy_AvgInLow * degree) / fuzzyLow); // Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �ǹ̰� ����.
    num_FuzzyAvgInLow = (double)num_LowZero - ((fuzzy_AvgInLow * degree) / fuzzyLow);
    // Low ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ּ����� ������
    // low ���� �� ���� ū ������  - (low ���� �� ������� ���� �� �ִ� �Ҽӵ� * degree) / low ������ü �� ������ �����ϴ� ����

    num_FuzzyAvgInHigh = ((fuzzy_AvgInHigh * degree) / fuzzyHigh) + (double)num_HighZero;
    // High ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ִ����� ������ ==
    // (high ���� �� ������� ���� �� �ִ� �Ҽӵ� * degree) / low ���ܿ��� �� ������ �����ϴ� ���� + ū �����͸� �Ǻ��ϴ� ���� ������

    avg_FuzzyAvg = (num_FuzzyAvgInHigh + num_FuzzyAvgInLow) / 2.0;
    fuzzyLowToAvg = (double)degree / (avg_FuzzyAvg - num_FuzzyAvgInLow);
    fuzzyAvgToHigh = (double)degree / (num_FuzzyAvgInHigh - avg_FuzzyAvg);

    // �� ���ܺ� fuzzy ���ϱ�
    for (i = 0; i < numLength; i++) {
        // �� ���ܵ��� ���� �� (0~1 ������ �Ǽ���) = (������ * (�ִ���� - �ּҹ���)) / degree
        // Fuzzy ���� ���� = 0.0 ~ 1.0
        // arr_FuzzyLow[i] = (fuzzyLow * (double)(num_LowLast - num[i])) / (double)degree;
        // �ٷ� �� ���� ������ Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �ǹ̰� ����.
        arr_FuzzyLow[i] = (fuzzyLow * (double)(num_LowZero - num[i])) / (double)degree;
        arr_FuzzHigh[i] = (fuzzyHigh * (double)(num[i] - num_HighZero)) / (double)degree;
        arr_FuzzyLowToAvg[i] = (fuzzyLowToAvg * (double)(num[i] - num_FuzzyAvgInLow)) / (double)degree;
        arr_FuzzyAvgToHigh[i] = (fuzzyAvgToHigh * (double)(num_FuzzyAvgInHigh - num[i])) / (double)degree;
    }

    // fuzzy print - low
    for (i = 0; i < numLength; i++) {
        if(arr_FuzzyLow[i] == 0.0){
            num_LowZero = num[i];
            break;
        }
    } // low fuzzy�� 0.0�� �����͸� num_LowZero�� �ְ� break

    fuzzyPrint("Low Fuzzy :\t\t", arr_FuzzyLow, numLength, 1);

    // fuzzy print - high
    fuzzyPrint("High Fuzzy :\t\t", arr_FuzzHigh, numLength, 1);

    // fuzzy print - average
    fuzzyPrint("LowToAvg Fuzzy :\t", arr_FuzzyLowToAvg, numLength, 2);
    fuzzyPrint("AvgToHigh Fuzzy :\t", arr_FuzzyAvgToHigh, numLength, 2);

    // fuzzy decision

    // num_FuzzyAvgInLow : Low ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ּ����� ������
    // num_FuzzyAvgInHigh :  High ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ִ����� ������
    // num_HighZero : High ���� fuzzy 0.0�϶��� ������
    // num_LowZero : Low ���� fuzzy 0.0�϶��� ������
    // num_Low : ��ü ���� �� ���� ���� ������

    // fuzzy point number print
    printf("\n");
    printf("number's sum :\t\t%.5lf\n", sum_Entire);
    printf("number's avg :\t\t%.5lf\n\n", avg_Entire);

    printf("number's low :\t\t%.5lf\n", num_Low);
    printf("number's avg 0.0 start: %.5lf\n", num_FuzzyAvgInLow);
    printf("number's low 0.0 :\t%.5lf\n", num_LowZero);
    printf("number's avg 1.0 :\t%.5lf\n", avg_FuzzyAvg);
    printf("number's high 0.0 :\t%.5lf\n", num_HighZero);
    printf("number's avg 0.0 end:\t%.5lf\n", num_FuzzyAvgInHigh);
    printf("number's high :\t\t%.5lf\n\n", num_High);

    printf("fuzzy decision:\t\t");
    for (i = 0; i < numLength; i++) {
        if (num[i] > num_FuzzyAvgInHigh) {
            // ��ü �����Ͱ� High ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ִ����� �����ͺ��� Ŭ ��� 'ũ��' ��� ǥ���Ѵ�.
            printf("TALL ");
        } else if (num[i] >= num_HighZero && num[i] < num_FuzzyAvgInHigh) {
            // ��ü �����Ͱ� High ���� fuzzy 0.0�϶��� �����ͺ��� ���ų� ũ�� num_FuzzyAvgInHigh���� ���� ��� '��պ��� ũ��' ��� ǥ���Ѵ�.
            printf("ATAL ");
        } else if (num[i] >= num_LowZero && num[i] < num_HighZero) {
            // ��ü �����Ͱ� Low ���� fuzzy 0.0�϶��� �����ͺ��� ���ų� ũ�� num_HighZero���� ���� ��� '����̴�' ��� ǥ���Ѵ�.
            printf("AVRG ");
        } else if (num[i] >= num_FuzzyAvgInLow && num[i] < num_LowZero) {
            // ��ü �����Ͱ� Low ���� �� Average ���ܿ� �Ҽӵ� �� �ִ� �ּ����� �����ͺ��� ���ų� ũ�� num_LowZero���� ���� ��� '��պ��� �۴�' ��� ǥ���Ѵ�.
            printf("AVSL ");
        } else if (num[i] >= num_Low) {
            // ��ü �����Ͱ� ��ü ���� �� ���� ���� �����ͺ��� ���ų� Ŭ ��� '�۴�' ��� ǥ���Ѵ�.
            printf("SMAL ");
        }
    }

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
