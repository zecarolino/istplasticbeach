/* multiply two numbers using a recursive function */
int product(int n1, int n2)
{
	if (n2 > 0) return (n1 + product(n1, n2 - 1));
	if (n2 < 0) return -product(n1, -n2);
	return 0;
}

int main() { return product(3, 4); }
