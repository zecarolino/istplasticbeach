int mem[10];
int main() {
	int *base = mem;
	mem[4] = 7;
	return base[4];
}
