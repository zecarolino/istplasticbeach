int f() { return 1; }
int g() { return 2; }
int h() { return 3; }
int (*ptr)();
int main() { ptr = g; return ptr(); }
