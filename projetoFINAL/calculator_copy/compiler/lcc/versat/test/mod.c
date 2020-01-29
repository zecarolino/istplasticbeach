int mod(int a, int b) {
	while (a >= b) a -= b;
	return a;
}

int main() {
	return mod(129, 5);
}
