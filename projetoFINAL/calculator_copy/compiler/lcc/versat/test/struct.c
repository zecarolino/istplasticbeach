struct a { int x, y, z, m, n; };
struct a func(struct a sa) { sa.y = 8; return sa; }
int main() {
	struct a stra;
	stra.x = stra.y = stra.z = 12; 
	stra = func(stra);
	return stra.y;
}
