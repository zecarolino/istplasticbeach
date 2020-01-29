/*
 * Fundamental to any permutation-generation algorithm is a notion of order,
 * the sequence in which the permutations are constructed, from first to last.
 * The most natural generation order is lexicographic, the order they would
 * appear if they were sorted numerically. Lexicographic order for n=3 is
 * {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}.
 * rank(p) = (p1 - 1) * (|p| - 1)! + rank({p2, ..., p|p|})
 * gives the position of 'p' in the given generation lexicographic order.
 * Getting this right means relabeling the elements of the smaller permutation
 * to reflect the deleted first element.
 */
int factorial(int n)
{
  if (n < 2) return 1;
  return n * factorial(n-1);
}

int rank(int *num, int siz)
{
  int i;

  if (siz < 1) return 0;

  /* num[0] gets removed so re-number all number above him, i.e,
   * make all remaining numbers in the range 1..(siz-1)
   */
  for (i = 1; i < siz; i++)
    if (num[i] > num[0])
      num[i]--;

  return (num[0] - 1) * factorial(siz - 1) + rank(num+1, siz-1);
}

#include "printf.h"
int main()
{
  int i, sum, n[10], j = 0, cnt;

  n[0] = 3;
  n[1] = 1;
  n[2] = 2;
  cnt = 3;

  for (i = sum = 0; i < cnt; i++, j+=i)
    sum += n[i];

  if (sum == 0 || sum != j) {
    printf("invalid sequence: it must contain all non-repeated numbers from 1 to n\n");
    return 1;
  }

  printf("rank{", sum, j);
  for (i = 0; i < cnt; i++)
    printf(" %d", n[i]);
  printf(" } = %d\n", rank(n, i));

  return 0;
}
