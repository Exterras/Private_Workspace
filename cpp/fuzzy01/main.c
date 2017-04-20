#include <stdio.h>
#include <stdlib.h>

// function prototype
void fileOpen();
void fuzzyOn();
void bubbleSort();

// struct
typedef struct data{
   float dataNum[];
} db;

// main
int main(){
    fileOpen(100);
    fuzzyOn();
    return 0;
}

void fileOpen(int _dbSize){
    FILE *fp = fopen("files/data.txt", "r");
    float data;
    float dbNum[_dbSize];
    int cnt = 0;

    while(0 < fscanf(fp, "%f", &data)){
        printf("%.2f ", data);
        db.dataNum[cnt] = data;
        cnt++;
    }
    printf("\n");
    fclose(fp);
}

// function of fuzzy execution
void fuzzyOn(){
    bubbleSort();
}

// function of bubble sort
void bubbleSort(){
    // variables
    int num[] = {64, 97, 87, 77, 54, 66, 81, 79, 88, 73}; // initialize value
    int i, j, temp; // bubble sort variables
    int highNum;
    int numLength = sizeof(num) / sizeof(num[0]);

    // before bubble sort
    printf("initialize value : ");
    for(i = 0; i < numLength; i++){
        printf("%d ",num[i]);
    }
    printf("\n");

    // highest value
    highNum = num[0];
    for(i = 0; i < numLength; i++){
        if(num[i] > highNum){
            highNum = num[i];
        }
    }

    // bubble sort
    for (i = 0; i < numLength; i++) {
        for (j = 0; j < numLength - i; j++) {
            if (num[j] > num[j+1]) {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
            }
        }
    }

    // before bubble sort
    printf("after bubble sort : ");
    for(i = 0; i < numLength; i++){
        printf("%d ",num[i]);
    }
    printf("\n");
}
