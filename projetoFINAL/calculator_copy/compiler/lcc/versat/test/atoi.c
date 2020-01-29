#include "mul.h"
#define EINVAL 22 /* from errno.h */
int errno;

int atoi(char *val)
{
  register char *ptr;
  register int i = 1, x;

  errno = 0;

  if (*val == '-') { val++; i = -1; }

  for (ptr = val; *ptr != 0; ptr++)
    if (*ptr < '0' || *ptr > '9')
      return errno = EINVAL, 0;
  
  for (x = 0; ptr > val; i *= 10)
    x += (*--ptr - '0') * i;

  return x;
}

#include "printi.h"
int main() { printi(597, 8); return 0; }
