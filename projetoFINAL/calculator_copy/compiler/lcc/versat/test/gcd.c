/* maior divisor comum entre dois numeros inteiros positivos */
int a = 144;
int b = 42;
/* expect 6 */

int main(int argc, char* *argv, char* *envp) {
  do {
    if (a > b)
      a = a - b;
    else
      b = b - a;
  } while (a != b);
  return a;
}
