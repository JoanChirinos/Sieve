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

// int bitwise_nth_prime(int n) {
//   if (n == 1) {
//     return 2;
//   }
//
//   // skipping 2
//   n--;
//
//   // lookup table for bits
//   // char* lookup;
//   // char l;
//   // for (l = -128; l < 128; l++) {
//   //   char x = l;
//   //   char counter = 0;
//   //   char bit_count;
//   //   for (bit_count = 0; bit_count < 8; bit_count++) {
//   //     if (x & 1<<(7 - bit_count)) counter++;
//   //   }
//   //   *(lookup + l + 128) = counter;
//   // }
//
//   float c = (n < 5000) ? 1.3 : 1.15; // constant for next step
//
//   // nth prime will be before this #
//   // we're dividing by 2 because we're not going to test evens
//   // we're also dividing by 8 because we're doing it bitwise
//   int max_index = ceil(((c * n * log(n)) / 2) / 8);
//
//   // allocated 1 byte for each num we're testing. sets all to 0
//   // calloc is (can be?) faster than allocating memory then zeroing
//   char* nums = calloc(sizeof(char), max_index);
//
//   // using this so we don't have to count from the beginning
//   // interesting --> this doesn't make it faster...
//   //int pcounter = 0;
//   //char* current_prime = NULL;
//
//   // starting at index 0
//   int char_index_at = 0;
//
//   // keeps the index of what bit we're at
//   int bit_index;
//
//   // traversing through indices till we get to sqrt(max_index)
//   for ( ; char_index_at * char_index_at <= max_index; char_index_at++) {
//
//     // traversing through the bits of the current index of char* nums
//     for (bit_index = 0; bit_index < 8; bit_index++) {
//       // printf("char_index_at: %d\nbit_index: %d\nrepresents: %d\nis currently: %d\n\n", char_index_at, bit_index, 2 * (char_index_at * 8 + bit_index + 1) + 1, *(nums + char_index_at) & 1 << (7 - bit_index));
//
//       // if num is prime
//       if (!(*(nums + char_index_at) & 1<<(7 - bit_index))) {
//         // printf("%d is prime\n\n", 2 * (char_index_at * 8 + bit_index + 1) + 1);
//
//         char* pointing_at = nums + char_index_at;
//         char* stop = nums + max_index;
//         int skip_by = 2 * (char_index_at * 8 + bit_index + 1) + 1;
//         int bit_at = bit_index;
//
//         // skip one first
//         bit_at += skip_by;
//         if (bit_at > 7) {
//           pointing_at += bit_at / 8;
//           bit_at %= 8;
//         }
//
//         while (pointing_at <= stop) {
//           // printf("\tpointing_at: %d\n\tbit_at: %d\n\trepresents: %d\n\tis currently: %d\n\n", pointing_at - nums, bit_at, 2 * ((pointing_at - nums) * 8 + bit_at + 1) + 1, *pointing_at & 1 << (7 - bit_at));
//
//           if (!(*pointing_at & 1 << (7 - bit_at))) {
//             *pointing_at = *pointing_at | 1 << (7 - bit_at);
//           }
//           // printf("\tis now: %d\n\n", *pointing_at & 1 << (7 - bit_at));
//           bit_at += skip_by;
//           if (bit_at > 7) {
//             bit_at %= 8;
//             pointing_at++;
//           }
//         }
//       }
//     }
//   }
//
//   // int t = 0;
//   // for ( ; t < max_index; t++) {
//   //   printf("%d: %d\n", t, (int)(*(nums + t)));
//   // }
//
//   // char* counting = nums;
//   // int counter = 0;
//   // while (counter < n) {
//   //   counter += *(lookup + *counting + 128);
//   //   counting++;
//   // }
//   //
//   // printf("ended counter at %d\n", counter);
//   // printf("counter has val %d\n", *counting);
//
//   return 0;
// }

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
  for ( ; i_at * i_at <= max_index; i_at++) {
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
