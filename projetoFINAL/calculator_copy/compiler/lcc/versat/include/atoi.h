#ifndef _ATOI_H_
#define _ATOI_H_

#include "mul.h"
#include "errno.h"

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

#endif /* _ATOI_H_ */
