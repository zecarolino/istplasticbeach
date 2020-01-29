int h() { return 4; }
int f(int (*g)()) { return g(); }
int main() { return f(h); }
