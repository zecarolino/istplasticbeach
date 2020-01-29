/* function cannot be named after any of the opcodes, 'add' for instance, or
   the assembeler will mess up */
int sum(int x, int y) { return x + y; }
int main() { return sum(5,4); }
