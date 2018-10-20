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

int sieve(int n) {
  if (n == 1) return 2;
  n--;

  // bit shift lookup table
  char* bit_shift_lookup_table = calloc(sizeof(char), 8);
  char i = 0;
  for( ; i < 8; i++) {
    *(bit_shift_lookup_table + i) = 1<<(7 - i);
  }

  // char to # of primes lookup table
  char* lookup_table = calloc(sizeof(char), 256);
  int lt;
  for (lt = -128; lt < 128; lt++) {
    char c = 0;
    char p;
    for (p = 0; p < 8; p++) {
      if (!(lt & *(bit_shift_lookup_table + p))) c++;
    }
    *(lookup_table + lt + 128) = c;
  }

  float c = (n < 5000) ? 1.3 : 1.15; // constant for next step

  // nth prime will be before this #
  // we're dividing by 16 because we're not going to test evens and we're using bits
  int max_index = ceil((c * n * log(n)) / 16);
  // printf("max_index: %d\n", max_index);

  // allocated 1 byte for each 8 nums we're testing. sets all to 0
  // calloc is (can be?) faster than allocating memory then zeroing
  char* nums = calloc(sizeof(char), max_index);

  int stop = ceil(sqrt(max_index));
  int main_char_index = 0;
  int main_bit_index = 0;

  while (main_char_index <= stop) {
    if (!(*(nums + main_char_index) & *(bit_shift_lookup_table + main_bit_index))) {

      int hop_by = 2 * (main_char_index * 8 + main_bit_index + 1) + 1;

      int sub_char_index = main_char_index;
      int sub_bit_index = main_bit_index;

      sub_bit_index += hop_by;
      if (sub_bit_index > 8) {
        sub_char_index += sub_bit_index / 8;
        sub_bit_index %= 8;
      }

      while (sub_char_index <= max_index) {
        if (!(*(nums + sub_char_index) & *(bit_shift_lookup_table + sub_bit_index))) {
          *(nums + sub_char_index) |= *(bit_shift_lookup_table + sub_bit_index);
        }
        sub_bit_index += hop_by;
        if (sub_bit_index >= 8) {
          sub_char_index += sub_bit_index / 8;
          sub_bit_index %= 8;
        }
      }
    }
    main_bit_index++;
    if (main_bit_index == 8) {
      main_bit_index = 0;
      main_char_index++;
    }
  }

  // ^ this is doing it right

  int prime_counter = 0;
  char* prime_char_at = nums;
  int prime_bit_at = 0;
  while (prime_counter <= n) {
    while(*prime_char_at & *(bit_shift_lookup_table + prime_bit_at)) {
      // printf("%d, %d --> %d --> is not prime\n", prime_char_at - nums, prime_bit_at, 2 * ((prime_char_at - nums) * 8 + prime_bit_at + 1) + 1);
      prime_bit_at++;
      if (prime_bit_at == 8) {
        prime_bit_at = 0;
        prime_char_at++;
      }
    }
    // printf("%d, %d --> %d --> is prime\n", prime_char_at - nums, prime_bit_at, 2 * ((prime_char_at - nums) * 8 + prime_bit_at + 1) + 1);
    prime_counter++;
    if (prime_counter == n) break;
    // printf("prime_counter is now %d\n", prime_counter);
    prime_bit_at++;
    if (prime_bit_at == 8) {
      prime_bit_at = 0;
      prime_char_at++;
    }
  }

  // printf("we got to the counter\n");
  // int prime_counter = 0;
  // char* prime_char_at = nums;
  // while (prime_counter < n) {
  //   prime_counter += *(lookup_table + *prime_char_at + 128);
  //   prime_char_at++;
  // }
  // printf("prime_counter: %d\n", prime_counter);
  // prime_counter -= *(lookup_table + *prime_char_at + 128);
  // printf("prime_counter: %d\n", prime_counter);
  // printf("*prime_char_at: %d\n", *prime_char_at);
  //
  // while (prime_counter >= n) {
  //   prime_counter -= *(lookup_table + *prime_char_at + 128);
  //   prime_char_at--;
  // }
  //
  // printf("prime_counter: %d\n", prime_counter);
  //
  // char prime_bit_at = 0;
  // while (prime_counter < n) {
  //   if (!(*prime_char_at & *(bit_shift_lookup_table + prime_bit_at))) prime_counter++;
  //   prime_bit_at++;
  // }

  // return 0;
  return 2 * ((prime_char_at - nums) * 8 + prime_bit_at + 1) + 1;
}

// avg time: 0.245 s on Stuy computer
//odds only
int odds_only(int n) {
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
