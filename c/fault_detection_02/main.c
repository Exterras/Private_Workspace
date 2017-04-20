#include <stdio.h>
#include <stdbool.h> // bool 타입을 사용하기 위한 라이브러리 삽입
#include "fileManager.h"

bool fault_detection(int _cnt, int _faultChkTimes, double _incPercent, double _minFault, double* _curData);

int main(){

    fault_detection(101, 10, 10, 0.2, file_save("Avg_D1_Nor_A_0_ABFault.txt"));
    return 0;
}

bool fault_detection(int _cnt, int _faultChkTimes, double _incPercent, double _minFault, double* _curData){
    int i, cnt = 0;
    int cntLen = _cnt;

    double highCur; // the most highest of this data (current)
    double minFault = _minFault; // the mininum of fault current
    double *curData = _curData; // para. file data to this func. data
    double transPer = ((_incPercent+100)/100); // percentage of rapid change current

    bool flag = false;

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
                printf("%.10lf *\n", curData[i+1]); // data print,
                // '*' means rapidly change current as compared with previous current
            } else {
                printf("%.10lf\n", curData[i+1]); // data print
            }

            if(curData[i+1] > curData[i] && curData[i+1] > highCur){
                highCur = curData[i+1];
                // 다음 전류와 이전 전류를 비교하여 큰 값에 highCur를 저장한다.
            }

        }
    }

    // 특정 카운트(cnt) 가 오류검출횟수(매개변수지정)보다 높을 경우 오류라고 인지하는 구문
    if(cnt >= _faultChkTimes && highCur >= minFault){
        printf("cnt : %d, fault", cnt);
        flag = true;
    } else {
        printf("cnt : %d, normal", cnt);
    }

    return flag;
}
