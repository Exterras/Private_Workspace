/**
* This is Fuzzy Program (C)
*
* by. Exterra (Tae-il Choi)
*
* "\t" is tab
*/

#include <stdio.h>
#include <stdlib.h>

// function prototype
void fuzzyOn(int *_num, int _numLength, int _degree, double _avgRate, int _num_LowZero, int _num_HighZero);
void fuzzyPrint(char* _str, double* _arrFuzzyValue, int _numLength, int _line); // fuzzy print function

// main
int main(){
    // fuzzy data and data length
    int num[] = {167, 484, 681, 486, 715, 351, 198, 189, 471, 648, 424, 843, 998}; // initialize value
    int numLength = sizeof(num) / sizeof(num[0]);

    // execute functions
    fuzzyOn(num, numLength, 100, 0.5, 400, 600);
    return 0;
}

// function of bubble sort
void fuzzyOn(int *_num, int _numLength, int _degree, double _avgRate, int _num_LowZero, int _num_HighZero){
    // general variables
    int* num = _num; // array parameter to pointer variable
    int i, j, temp; // bubble sort and iteration variables
    int sum_Entire = 0; // array's sum
    double avg_Entire = 0.0; // array's avg
    double avgRate = _avgRate; // low and high rate = average's start and end point

    // data variables
    int numLength = _numLength; // array's length

    // Low 0.0�� �ش��ϴ� ���� �Ű������� �޾��� �� �� ������ �������� �ʴ´�.
    // int num_LowLast = 0; // low last in an array,

    int num_High; // array highest number, high 1.0's number
    int num_Low; // array lowest number, low 1.0's number
    int num_HighZero = _num_HighZero; // high 0.0's number
    int num_LowZero = _num_LowZero; // // low 0.0's number

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
        printf("%d ",num[i]);
    }
    printf("\n");



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

    // after bubble sort (Ascending)
    printf("after B.S. (Asc.):\t");
    for(i = 0; i < numLength; i++){
        printf("%d ",num[i]);
    }
    printf("\n"); // carriage return

    // after bubble sort (Descending)
    //printf("after B.S. (Desc.):\t");
    //for(i = numLength-1 ; i >= 0; i--){
    //    printf("%d ",num[i]);
  //  }
    printf("\n"); // carriage return

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
    printf("number's sum :\t\t%d\n", sum_Entire);
    printf("number's avg :\t\t%.2lf\n\n", avg_Entire);

    printf("number's low :\t\t%d\n", num_Low);
    printf("number's avg 0.0 start: %.2lf\n", num_FuzzyAvgInLow);
    printf("number's low 0.0 :\t%d\n", num_LowZero);
    printf("number's avg 1.0 :\t%.2lf\n", avg_FuzzyAvg);
    printf("number's high 0.0 :\t%d\n", num_HighZero);
    printf("number's avg 0.0 end:\t%.2lf\n", num_FuzzyAvgInHigh);
    printf("number's high :\t\t%d\n\n", num_High);

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
