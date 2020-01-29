#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "printi.h"
#include "puts.h"
#include "stdarg.h"

int printf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  while (*fmt != 0) {
    if (*fmt == '%') {
      fmt++;
      if (*fmt == 'd') printi(va_arg(ap,int), 10);
      else if (*fmt == 's') puts(va_arg(ap,char*));
      else if (*fmt == 'c') putchar(va_arg(ap,int));
      else putchar(*fmt);
    }
    else putchar(*fmt);
    fmt++;
  }
  va_end(ap);
  return 1;
}

#endif /* _PRINTF_H_ */
