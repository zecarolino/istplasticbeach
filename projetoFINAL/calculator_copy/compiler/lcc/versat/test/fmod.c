int _mod(int a, int b) {
	while (a >= b) a -= b;
	return a;
}
int main() { return 129 % 5; }
