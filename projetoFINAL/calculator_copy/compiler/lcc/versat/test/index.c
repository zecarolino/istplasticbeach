int mem[10], *base = mem;
int main() {
	base[6] = 9;
	return mem[6];
}
