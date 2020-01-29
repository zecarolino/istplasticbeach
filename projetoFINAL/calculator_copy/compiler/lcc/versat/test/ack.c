int cnt=0;
ackermann(m, n) {
  cnt = cnt + 1;
  if (m == 0) return (n+1);
  if (n == 0) return (ackermann(m-1, 1));
  return (ackermann(m-1, ackermann(m, n-1)));
}

#include "printi.h"
main(int argc, char *argv[]) {
  printi(ackermann(2, 4), 10);
  putchar('\n');
  printi(cnt, 10);
  putchar('\n');
  return (0);
}

/* ack(2,4)=11 #65 ack(3,2)=29 #541 */
