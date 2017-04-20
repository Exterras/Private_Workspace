#include <stdio.h>
#include <stdlib.h>

int file_open(char* _fileName){
    FILE *fp;
    int cnt;
    double data;

    fp = fopen(_fileName, "r");
    if(fp == NULL){ printf("fail"); }
    while(fscanf(fp, "%lf", &data)!= EOF){
       // printf("%.10lf\n", data);
        cnt++;
    }
    return cnt;
}

double* file_save(char* _fileName){
    FILE *fp;
    int i, cnt;
    double data;

    cnt = file_open(_fileName);
    double curData[cnt];

    //curData = (double*)malloc(sizeof(int)*cnt);

    fp = fopen(_fileName, "r");
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
       // printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);
    return curData;
}
