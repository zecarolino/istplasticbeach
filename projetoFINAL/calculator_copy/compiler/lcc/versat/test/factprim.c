#include "printf.h"

int nextPrime(int n)
{
  int i;

  if (n <= 0) return 0;
  if (n <= 2) return n+1;
  while (++n > 0) {
    if (n % 2 == 0) continue; /* is even */
    for (i = 3; i < n; i += 2) /* test odd numbers */
      if (n % i == 0)
	break;
    if (i >= n)
      return n;
  }
  return 0; /* overflow */
}

void factprim(int num)
{
  int cnt, n = 1;

  while (n < num) {
    n = nextPrime(n);
    for (cnt = 0; num % n == 0; cnt++)
      num /= n;
    if (cnt != 0)
      printf(" * %d^%d", n, cnt);
  }
  printf("\n");
}

int main()
{
  factprim(144); /* expect ' * 2^4 * 3^2' */
  return 0;
}
