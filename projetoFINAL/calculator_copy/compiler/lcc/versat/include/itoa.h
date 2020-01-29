#ifndef _ITOA_H_
#define _ITOA_H_

#include "mod.h"

char buf[32];
char *itoa(int i)
{
  int sign = 0;
  char *ptr = buf+15;

  if (i < 0) { sign++; i = -i; }
  *ptr = 0; /* put NULL */
  do {
    *--ptr = '0' + i%10;
  } while ((i = i/10) > 0);
  if (sign != 0) *--ptr = '-';
  return ptr;
}

#endif /* _ITOA_H_ */
