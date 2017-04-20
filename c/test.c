#include <stdio.h>
main()
{
   int a[2][3] = {{1,2,3},{4,5,6}};

   int sum = 0;
   int max = 0;

   int c, h;

   // int ctotal[sizeof(a)];
   // int htotal2[sizeof(a[0])];

   int ctotal = 0;
   int ctotal1 = 0;
   int htotal = 0;
   int htotal1 = 0;
   int htotal2 = 0;


   //
   //123
   //456 형태의 출력

   //sum,,max 구하기

   //123 | 6
   //456 | 15


   //123 |6
   //456 | 15
   //--------
   //579

   // 123, 456
   for (c = 0; c < 2; c++){
      for (h = 0; h < 3; h++){
        printf("%d", a[c][h]); // 123, 456 출력

        sum += a[c][h];
         if (max < a[c][h])
         {
            max = a[c][h];
         }
      }
      printf("\n");
   }

   // 배열의 합과 배열의 값을 비교하여 최댓값을 도출
   printf("sum : %d\n", sum);
   printf("max : %d\n", max);
   printf("\n");

   for (c = 0; c < 1; c++){
      for (h = 0; h < 3; h++){
         printf("%d", a[c][h]);
         ctotal += a[c][h];
      }
      printf("| %d\n", ctotal);
   }

   for (c = 1; c < 2; c++){
      for (h = 0; h < 3; h++){
         printf("%d", a[c][h]);
         ctotal1 += a[c][h];
      }
      printf("| %d\n\n", ctotal1);
   }

   ////////////////////////////////////////////////////

   if(c == 0){
    for (h = 0; h < 3; h++){
         printf("%d", a[c][h]);
      }
      printf("| %d\n", ctotal);
   }

   if(c == 1){
    for (h = 0; h < 3; h++){
         printf("%d", a[c][h]);
      }
      printf("| %d\n", ctotal1);
   }

   printf("--------\n");
/////////////////////////////////////////////

   for (c = 0; c < 2; c++){
      for (h = 0; h < 1; h++){
         htotal += a[c][h];
      }

      for (h = 1; h < 2; h++){
         htotal1 += a[c][h];
      }

      for (h = 2; h < 3; h++){
         htotal2 += a[c][h];
      }
   }
   printf("%d", htotal);
   printf(" %d", htotal1);
   printf(" %d\n", htotal2);
}
