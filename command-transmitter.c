#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int get_influence_index(int param_1)
{
  return (param_1 * 13 + 7) % 16;
}


bool char_is_uppercase(char c)
{
  bool is_upper;
  
  if ((c < 'A') || ('Z' < c)) {
    is_upper = false;
  }
  else {
    is_upper = true;
  }
  return is_upper;
}


char switch_char_case(char param_1)
{
  return param_1 ^ 32;
}


bool char_is_even(char param_1)
{
  return (param_1 & 1) == 0;
}

char* fill_string_with_A(char* param_1)

{
  *(unsigned long*)param_1 = 0x4141414141414141;
  *(unsigned long*)(param_1 + 8) = 0x4141414141414141;
  param_1[16] = '\0';
  return param_1;
}


char* command_transmitter(char *param_1)
{
  bool isupper;
  char newchar;
  char c;
  char* __dest;
  size_t length;
  int curr_index;
  int influence_index;
  int next_index;
  
  __dest = (char*)malloc(16);
  length = strlen(param_1);
  if (length == 16) {
    strcpy(__dest,param_1);
    curr_index = 0;
    influence_index = 7;
    next_index = curr_index;
    while (curr_index = next_index, influence_index != 0) {
      influence_index = get_influence_index(curr_index);
      c = param_1[influence_index];
      isupper = char_is_uppercase(c);
      if (isupper) {
        newchar = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = newchar;
      }
      isupper = char_is_even(c);
      next_index = influence_index;
      if (isupper) {
        c = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = c;
      }
    }
  }
  else {
    __dest = fill_string_with_A(__dest);
  }
  return __dest;
}


int main()
{
  char* target = "quietrobotplease";
  char sol[16+1];
  for (int i = 0; i < (1<<16); i++)
  {
    strcpy(sol, target);
    for (int j = 0; j < 16; j++)
      if((1<<j) & i)
        sol[j] = switch_char_case(sol[j]);
    char* scrambled = command_transmitter(sol);
    if (!strcmp(scrambled, target))
      printf("%d: %s -> %.16s\n", i, sol, scrambled);
  }

  return 0;
}
