int mem[10], *base;
int main() {
	base = mem;
	mem[3] = 5;
	return base[3];
}
