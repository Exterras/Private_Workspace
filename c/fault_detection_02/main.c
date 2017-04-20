#include <stdio.h>
#include <stdbool.h> // bool Ÿ���� ����ϱ� ���� ���̺귯�� ����
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
                printf("%.10lf *\n", curData[i+1]); // data print,
                // '*' means rapidly change current as compared with previous current
            } else {
                printf("%.10lf\n", curData[i+1]); // data print
            }

            if(curData[i+1] > curData[i] && curData[i+1] > highCur){
                highCur = curData[i+1];
                // ���� ������ ���� ������ ���Ͽ� ū ���� highCur�� �����Ѵ�.
            }

        }
    }

    // Ư�� ī��Ʈ(cnt) �� ��������Ƚ��(�Ű���������)���� ���� ��� ������� �����ϴ� ����
    if(cnt >= _faultChkTimes && highCur >= minFault){
        printf("cnt : %d, fault", cnt);
        flag = true;
    } else {
        printf("cnt : %d, normal", cnt);
    }

    return flag;
}
