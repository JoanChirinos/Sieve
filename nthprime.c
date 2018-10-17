#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int nth_prime(n) {
  float c = (n < 5000) ? 1.3 : 1.15;
  int max_index = ceil(c * n * log(n));
  char* nums = calloc(sizeof(char), max_index); // all set to 0
  int at = 2;
  for ( ; at * at <= max_index; at++) {
    if (!(*(nums + at))) {
      char* x = nums + at + at;
      for ( ; x < nums + max_index; x += at) {
        if (!(*(x))) *x = 1;
      }
    }
  }

  char* onums = nums;

  for ( ; n >= -1; n--) {
    //printf("%d\n", nums);
    while (*nums != 0) {
      nums += 1;
    }
    nums += 1;
  }
  nums -= 1;

  // char* r = nums;
  // int w;
  // for(w = 0; w < max_index; w++) {
  //   printf("%d: %d\n", w, *(r + w));
  // }

  return nums - onums;
}

int main() {
  struct timeval stop, start;
  int x;
  gettimeofday(&start, NULL);
  x = nth_prime(1000000);
  gettimeofday(&stop, NULL);
  printf("100th prime: %d\n", x);
  printf("took %lu microseconds\n", (stop.tv_usec - start.tv_usec));
}
