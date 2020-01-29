int mem[10];
int main() {
	int *base = mem;
	base[6] = 8;
	return mem[6];
}
