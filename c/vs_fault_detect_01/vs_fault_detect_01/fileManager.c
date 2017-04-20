#include <stdio.h>
#include <stdlib.h>

// 파일을 열어주는 함수
int file_open(char *_fileName){
    FILE *fp;
    int cnt;
    double data;

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

double* file_save(char *_fileName){
    FILE *fp;
    int i, cnt;
    double data;

    // 파일을 저장하기 위해 앞선 함수를 호출하여 그 리턴값을 받아들임
    cnt = file_open(_fileName);

    // 파일의 갯수만큼 동적 할당 배열(curData)을 만든다. 그리고 그 값에 파일을 저장한다.
    double *curData = (double*)malloc(sizeof(int)*cnt);

    fp = fopen(_fileName, "r");
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
        // printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);

    // 저장된 파일의 포인터를 리턴한다.
    return curData;
}

