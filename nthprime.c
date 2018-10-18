#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int nth_prime(int n) {
  if (n == 1) {
    return 2;
  }
  // skipping 2
  n--;
  float c = (n < 5000) ? 1.3 : 1.15; // constant for next step
  // nth prime will be before this #
  // we're dividing by 2 because we're not going to test evens
  int max_val = ceil(c * n * log(n));
  int max_index = max_val / 2;

  // allocated 1 byte for each num we're testing. sets all to 0
  // calloc is (can be?) faster than allocating memory then zeroing
  char* nums = calloc(sizeof(char), max_index);

  // starting at index 0
  int i_at = 0;

  // traversing through indices till we get to sqrt(max_index)
  for ( ; i_at * i_at <= max_index; i_at++) {

    // if the num stored at i_at isn't prime
    if (!(*(nums + i_at))) {

      int hop_by = 2 * (i_at + 1) + 1;
      char* x = nums + i_at + hop_by;
      char* stop = nums + max_index;
      for ( ; x < stop; x += hop_by) {
        if (!(*(x))) *x = 1;
      }
    }
  }

  char* p = nums;

  for ( ; n >= 0; n--) {
    while (*nums != 0) {
      nums += 1;
    }
    nums += 1;
  }
  nums -= 1;

  return 2 * ((nums - p) + 1) + 1;
}

int old_nth_prime(int n) {
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
  //printf("1000000th prime: %d\n", old_nth_prime(1000000));
  printf("1000000th prime: %d\n", nth_prime(1000000));

  return 0;
}
