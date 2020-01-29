int f() { return 1; }
int g() { return 2; }
int h() { return 3; }
int (*v[])() = { f, g, h };
int main() { return v[2](); }
