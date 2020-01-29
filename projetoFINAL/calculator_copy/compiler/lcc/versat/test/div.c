int div(int a, int b) {
	int x = 0;
	while (a >= b) a -= b, x++;
	return x;
}

int main() {
	return div(38, 5);
}
