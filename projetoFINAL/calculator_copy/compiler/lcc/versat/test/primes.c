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

#include "printf.h"
int main()
{
  int max = 20, n = 1, cnt = 0;

  while (n < max && n > 0)
    printf("%d: %d\n", ++cnt, n = nextPrime(n));

  return 0;
}
