#include <stdio.h>

/*int main()
{
    // 합을 구할 숫자와 그의 갯수를 입력받는 변수 설정
    int cnt;
    int num;

    // 안내문
    printf("합을 구할 숫자와 그의 개수를 적으시오\n");

    // 입력붐
    scanf("%d", &cnt);
    scanf("%d", &num);

    printf("\n");

    calcu(cnt, num);
    return 0;
}*/

int main(){
    char a = 0xff;

    printf("%x", a);

    return 0;
}

// 사용자로부터 입력받을 받아서 처리하는 함수 (갯수, 합을 구할 숫자)
void calcu(int _cnt, int _num){

    // 변수 선언 (반복획수, 합계변수, 숫자를 분리할 배열선언, 뱅열의 길이)
    int i, sum = 0;
    int num[_cnt];
    int arrLength = sizeof(num) / sizeof(num[0]);

    // 입력받은 숫자를 분리하는 수식
    for(i = 0; i < arrLength; i++){
        if(i == 0){
            num[i] = _num % 10;
        } else {
            _num = _num / 10;
            num[i] = _num % 10;
        }
    }

    // 분리한 수식을 합산하는 수식
    for(i = 0; i < arrLength; i++){
        sum += num[i];
    }

    // 출력문
    printf("합의 결과 : %d\n", sum);
}

