#include <stdio.h>
#include <stdlib.h>

// ������ �����ִ� �Լ�
int file_open(char *_fileName){
    FILE *fp;
    int cnt;
    double data;

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

double* file_save(char *_fileName){
    FILE *fp;
    int i, cnt;
    double data;

    // ������ �����ϱ� ���� �ռ� �Լ��� ȣ���Ͽ� �� ���ϰ��� �޾Ƶ���
    cnt = file_open(_fileName);

    // ������ ������ŭ ���� �Ҵ� �迭(curData)�� �����. �׸��� �� ���� ������ �����Ѵ�.
    double *curData = (double*)malloc(sizeof(int)*cnt);

    fp = fopen(_fileName, "r");
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
        // printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);

    // ����� ������ �����͸� �����Ѵ�.
    return curData;
}

