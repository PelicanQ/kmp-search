#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// KMP substring search algorithm deduced from https://www.youtube.com/watch?v=GTJr8OvyEVQ

size_t *make_helper(char *pattern, size_t patlen)
{
  size_t *helper = malloc(patlen * sizeof(size_t));
  helper[0] = 0;
  int j = 0;
  int i = 1;

  // First we generate the helper array.
  // A value at index i in this arrays says the length of the longest pattern prefix which equals the suffix up to position i.
  while (i < patlen)
  {
    if (pattern[i] == pattern[j])
    {
      helper[i] = j + 1;
      i++;
      j++;
    }
    else if (j > 0 && helper[i - 1] > 0)
    {
      j = helper[j - 1];
    }
    else
    {
      helper[i] = 0;
      i++;
    }
  }
  return helper;
}

int kmp(char *text, char *pattern)
{
  size_t patlen = strlen(pattern);
  size_t textlen = strlen(text);

  if (patlen < 2)
  {
    printf("Give me a longer pattern\n");
    exit(EXIT_FAILURE);
  }
  size_t *helper = make_helper(pattern, patlen);
  int c = 0; // starting position in text
  int p = 0; // position in pattern
  while (p < patlen && c < textlen)
  {
    if (pattern[p] == text[c])
    {
      p++;
      c++;
    }
    else
    {
      if (p == 0)
      {
        c++;
      }
      else
      {
        p = helper[p - 1];
      }
    }
  }
  if (p == patlen)
  {
    // found
    return c - p;
  }
  else
  {
    // not found
    return -1;
  }
}

int main(int argc, char **argv)
{
  char *text = "ababcabcdab";
  char *pattern = "abcd";

  int pos = kmp(text, pattern);
  printf("Found in: %d\n", pos);
  return 0;
}