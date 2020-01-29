#include "printi.h"
int main()
{
  int n = 16, i = 0, j = 1, *seg = &i;

  while (n-- > 0) {
    putchar(' ');
    printi(*seg = i + j, 10);
    seg = (seg == &i) ? &j : &i;
  }
  putchar('\n');
  return 0;
}
