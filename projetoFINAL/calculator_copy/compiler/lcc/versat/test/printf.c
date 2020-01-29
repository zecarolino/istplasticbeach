#include "printi.h"
#include "puts.h"

typedef int *va_list;
#define va_start(ap,fmt) ((ap)=(va_list)&(fmt))
#define va_arg(ap,type) ((type)*++ap)
#define va_end(ap)

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

int main() {
	printf("Hell%c w%s!\n642=%d\n", 'o', "orld", 642);
	return 0;
}
