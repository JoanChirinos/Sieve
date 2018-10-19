#include <stdio.h>
#include <stdlib.h>

int main() {
  // char* n = calloc(sizeof(char), 2);
  // *n = 'x';
  // *(n + 1) = 'D';
  // int length = sizeof(char) * 2 * 8;
  // int i;
  // int x;
  // for (x = 0; x < 2; x++) {
  //   printf("doing %c\n", *n);
  //   for (i = 0; i < 8; i++) {
  //     // 1<<(8 - i)  --> if i = 4, this -> 00001000
  //     if ((*n & (1 << (7 - i))) != 0) {
  //       printf("bit at index %d is a 1\n", i);
  //     }
  //     else {
  //       printf("bit at index %d is a 0\n", i);
  //     }
  //   }
  //   n++;
  // }
  // return 0;
  // char* n = calloc(sizeof(char), 1);
  // printf("*n is %d\n", *n);
  // int i = 0;
  // for ( ; i < 8; i++) {
  //   *n = *n | 1 << (7 - i);
  //   int x = 0;
  //   for ( ; x < 8; x++) {
  //     if (*n & 1 << (7 - x)) {
  //       printf("1");
  //     }
  //     else printf("0");
  //   }
  //   printf("\n");
  // }

  char x = 11;
  char counter = 0;
  char bit_count;
  for (bit_count = 0; bit_count < 8; bit_count++) {
    if (!(x & 1<<(7 - bit_count))) counter++;
  }

  printf("%d has %d primes\n", x, counter);

  return 0;
}
