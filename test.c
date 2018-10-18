#include <stdio.h>
#include <stdlib.h>

int main() {
  char* n = calloc(sizeof(char), 2);
  *n = 'x';
  *(n + 1) = 'D';
  int length = sizeof(char) * 2 * 8;
  int i;
  int x;
  for (x = 0; x < 2; x++) {
    printf("doing %c\n", *n);
    for (i = 0; i < 8; i++) {
      // 1<<(8 - i)  --> if i = 4, this -> 00001000
      if ((*n & (1 << (7 - i))) != 0) {
        printf("bit at index %d is a 1\n", i);
      }
      else {
        printf("bit at index %d is a 0\n", i);
      }
    }
    n++;
  }
  return 0;
}
