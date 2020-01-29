int main() {
	int a = 3, b = 3, mul, i;
	for (mul = i = 0; i < 32; i++)
		if (b & (1 << i))
			mul += a << i;
		else /* optimize if upper bits are zero */
			if (!(b >> i))
				break;
	
	return mul;
}
