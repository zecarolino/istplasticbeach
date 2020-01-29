int func(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k) {
	a = a + b - c - d - e + f - g + h + i + j + k;
	b = a - b + c + d - e - f + g - h + i - j - k;
	c = a + b - c - d + e + f + g - h + i + j - k;
	d = a - b - c + d - e + f - g + h - i - j - k;
	e = a + b + c - d - e - f - g + h - i + j - k;
	f = a - b - c + d - e + f + g - h - i - j + k;
	g = a + b - c - d + e + f + g - h + i + j - k;
	h = a - b + c + d - e - f - g + h + i - j - k;
	i = a + b - c - d - e + f + g + h + i + j - k;
	j = a - b - c + d - e + f + g - h - i - j - k;
	k = a + b + c - d + e - f - g - h - i + j + k;
	return a + b + c + d + e + f - g + h - i + j - k;
}

int main() {
	return func(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
}
