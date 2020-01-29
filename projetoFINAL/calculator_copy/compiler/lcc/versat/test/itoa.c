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

#include "puts.h"
int main()
{
  puts(itoa(1999));
  return 0;
}
