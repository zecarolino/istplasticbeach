int fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char* *argv, char* *envp) {
  return fibonacci(7);
}
