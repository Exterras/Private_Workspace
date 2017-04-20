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

    // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 변수는 쓰여지지 않는다.
    // int num_LowLast = 0; // low last in an array,

    int num_High; // array highest number, high 1.0's number
    int num_Low; // array lowest number, low 1.0's number
    int num_HighZero = _num_HighZero; // high 0.0's number
    int num_LowZero = _num_LowZero; // // low 0.0's number

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

   // low fuzzy 중 데이터가 가장 큰 변수를 골라내는 과정,
   // Low 0.0에 해당하는 값을 매개변수로 받았을 때 이 과정은 의미가 없다.
   // for (i = 0; i < numLength; i++) {
   //     if (num[i] < avg_Entire) {
   //         num_LowLast = num[i];
   //     }
   // }

    // 사용자가 설정한 degree 나누기 각 소속 집단별로 최대값과 최소값를 구하여 그 차액 -> 전체 집단에서 한 눈금이 차지하는 비율
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
    } // low fuzzy가 0.0인 데이터를 num_LowZero에 넣고 break

    fuzzyPrint("Low Fuzzy :\t\t", arr_FuzzyLow, numLength, 1);

    // fuzzy print - high
    fuzzyPrint("High Fuzzy :\t\t", arr_FuzzHigh, numLength, 1);

    // fuzzy print - average
    fuzzyPrint("LowToAvg Fuzzy :\t", arr_FuzzyLowToAvg, numLength, 2);
    fuzzyPrint("AvgToHigh Fuzzy :\t", arr_FuzzyAvgToHigh, numLength, 2);

    // fuzzy decision

    // num_FuzzyAvgInLow : Low 집단 중 Average 집단에 소속될 수 있는 최소한의 데이터
    // num_FuzzyAvgInHigh :  High 집단 중 Average 집단에 소속될 수 있는 최대한의 데이터
    // num_HighZero : High 집단 fuzzy 0.0일때의 데이터
    // num_LowZero : Low 집단 fuzzy 0.0일때의 데이터
    // num_Low : 전체 집단 중 가장 작은 데이터

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
            // 전체 데이터가 High 집단 중 Average 집단에 소속될 수 있는 최대한의 데이터보다 클 경우 '크다' 라고 표현한다.
            printf("TALL ");
        } else if (num[i] >= num_HighZero && num[i] < num_FuzzyAvgInHigh) {
            // 전체 데이터가 High 집단 fuzzy 0.0일때의 데이터보다 같거나 크고 num_FuzzyAvgInHigh보다 작을 경우 '평균보다 크다' 라고 표현한다.
            printf("ATAL ");
        } else if (num[i] >= num_LowZero && num[i] < num_HighZero) {
            // 전체 데이터가 Low 집단 fuzzy 0.0일때의 데이터보다 같거나 크고 num_HighZero보다 작을 경우 '평균이다' 라고 표현한다.
            printf("AVRG ");
        } else if (num[i] >= num_FuzzyAvgInLow && num[i] < num_LowZero) {
            // 전체 데이터가 Low 집단 중 Average 집단에 소속될 수 있는 최소한의 데이터보다 같거나 크고 num_LowZero보다 작을 경우 '평균보다 작다' 라고 표현한다.
            printf("AVSL ");
        } else if (num[i] >= num_Low) {
            // 전체 데이터가 전체 집단 중 가장 작은 데이터보다 같거나 클 경우 '작다' 라고 표현한다.
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
