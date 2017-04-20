#include <stdio.h>
#include <stdlib.h>

int file_open(char* _fileName, char* _accessChar);
void file_save(char* _fileName, char* _accessChar, int _cnt);

int main(){
    int cnt;

    cnt = file_open("Avg_D1_Nor_A_0_ABFault.txt", "r");
    file_save("Avg_D1_Nor_A_0_ABFault.txt", "r", cnt);

    return 0;
}

int file_open(char* _fileName, char* _accessChar){
    FILE *fp;
    int cnt;
    double data;

    fp = fopen(_fileName, _accessChar);
    if(fp == NULL){ printf("fail"); }
    while(fscanf(fp, "%lf", &data)!= EOF){
       // printf("%.10lf\n", data);
        cnt++;
    }
    fclose(fp);
    return cnt;
}

void file_save(char* _fileName, char* _accessChar, int _cnt){
    FILE *fp;
    int i = 0;
    double data;
    double curData[_cnt];

    fp = fopen(_fileName, _accessChar);
    while(fscanf(fp, "%lf", &data)!= EOF){
        curData[i] = data;
        printf("%.10lf\n", curData[i]);
        i++;
    }
    fclose(fp);
}
