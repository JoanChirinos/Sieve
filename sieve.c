#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sieve.h"

// After correctly labeling primes and composites:
// - Don't look for nth prime by checking each bit.
//   - Have a lookup table with what char corresponds to how mnay primes
//   - e.g. If the char is 00000111, which is 7, you can do *(lookup_table + 7) = 5
//     which is the number of 0s in the byte. This way, you only have to go through
//     all the bits in each combination once rather than at every byte you look at
// - You might run into a complication: you will likely count too high
//   - To fix this, count too high then count down the remaining x bit until you get
//     to the bit/byte combo which represents the nth prime

int bitwise_sieve(int n) {
  if (n == 1) return 2;
  n--;

  float c = (n < 5000) ? 1.3 : 1.15; // constant for next step

  // nth prime will be before this #
  // we're dividing by 16 because we're not going to test evens and we're using bits
  int max_index = ceil((c * n * log(n)) / 16);

  // allocated 1 byte for each 8 nums we're testing. sets all to 0
  // calloc is (can be?) faster than allocating memory then zeroing
  char* nums = calloc(sizeof(char), max_index);

  int main_index = 0;





  return 0;
}

// avg time: 0.245 s on Stuy computer
//odds only
int sieve(int n) {
  if (n == 1) {
    return 2;
  }

  // skipping 2
  n--;

  float c = (n < 5000) ? 1.3 : 1.15; // constant for next step

  // nth prime will be before this #
  // we're dividing by 2 because we're not going to test evens
  int max_index = ceil(c * n * log(n) / 2);
  // printf("max_index: %d\n", max_index);

  // allocated 1 byte for each num we're testing. sets all to 0
  // calloc is (can be?) faster than allocating memory then zeroing
  char* nums = calloc(sizeof(char), max_index);

  // starting at index 0
  int i_at = 0;

  int prime_counter = 0;
  char* current_prime = nums;

  int stop = ceil(sqrt(max_index));

  // traversing through indices till we get to sqrt(max_index)
  for ( ; i_at <= stop; i_at++) {
    if (!(*(nums + i_at))) {
      prime_counter++;
      // printf("prime_counter: %d\n", prime_counter);
      current_prime = nums + i_at;
      // printf("current prime index: %ld\n", nums - current_prime);
      // printf("current prime valule: %ld\n", 2 * (current_prime - nums + 1) + 1);
      int hop_by = 2 * (i_at + 1) + 1;
      char* x = nums + i_at + hop_by;
      char* stop = nums + max_index;
      for ( ; x < stop; x += hop_by) {
        if (!(*(x))) *x = 1;
      }
    }
  }

  while (prime_counter < n) {
    if (!(*current_prime)) prime_counter++;
    current_prime++;
  }

  return 2 * (current_prime - nums + 1) + 1;
}

// keeps evens
int all_nth_prime(int n) {
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
