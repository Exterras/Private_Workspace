#include <stdio.h>
#include <stdlib.h>
#include <string.h> // ���ڿ� �Ϻ� ���Ÿ� ���� strcpy()�� ����� �� �ִ� ���̺귯�� ��
#include <stdbool.h> // bool Ÿ���� ����ϱ� ���� ���̺귯�� ����

#include "fileManager.h" // ���� ������� ���� ���̺귯�� ����
#include "fault_check.h" // ������ �����Ͽ��� �� ������ �Ǻ��ϴ� ���̺귯�� ����

double minFault = 0.2;

typedef struct faultChkValue {
    char *curName;
    int curLen;
    int faultChkTimes;
    double incPercent;
    int cnt;
} chk;

void fault_detection(void);
void input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent);
void fault_handler(int _cnt, int _faultChkTimes);
void string_delete(char *_str, char _delStr);

void fault_detection(void){
}

void input_data(chk _current, char* _data, int _curLen, int _faultChkTimes, double _incPercent){
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
    // string_delete(_data, 't');
    printf("%s -> ", _data);
    fault_handler(_current.cnt, _current.faultChkTimes);
}

void fault_handler(int _cnt, int _faultChkTimes){
    if(_cnt >= _faultChkTimes){
        printf("cnt : %d, fault\n", _cnt);
    } else {
        printf("cnt : %d, normal\n", _cnt);
    }
    _cnt = 0;
}

// error occurred
void string_delete(char *_str, char _delStr){
    for(; *_str!='\0'; _str++){
        if(*_str == _delStr){
            strcpy(_str, _str+1);
            _str--;
        }
    }
}

int main()
{
    chk cur_A[3], cur_B[3];
    chk cur_C[3];

    input_data(cur_A[0], "A_0.txt", 101, 10, 10);
    input_data(cur_A[1], "A_45.txt", 101, 10, 10);
    input_data(cur_A[2], "A_90.txt", 101, 10, 10);

    input_data(cur_B[0], "B_0.txt", 101, 10, 10);
    input_data(cur_B[1], "B_45.txt", 101, 10, 10);
    input_data(cur_B[2], "B_90.txt", 101, 10, 10);

    /*
    int a = fault_check(101, 10, 10, minFault, file_save("C_0.txt"));
    printf("C_0.txt -> ");
    fault_handler(a, 10);

    int b = fault_check(101, 10, 10, minFault, file_save("C_45.txt"));
    printf("C_45.txt -> ");
    fault_handler(b, 10);

    int c = fault_check(101, 10, 10, minFault, file_save("C_90.txt"));
    printf("C_90.txt -> ");
    fault_handler(c, 10);
    */

    input_data(cur_C[0], "C_0.txt", 101, 10, 10);
    input_data(cur_C[1], "C_45.txt", 101, 10, 10);
    input_data(cur_C[2], "C_90.txt", 101, 10, 10);

    return 0;
}
