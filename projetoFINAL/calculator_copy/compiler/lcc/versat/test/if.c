int x = 4, y = 4, z = 4;
int main() {
	int s = 0;
	if (x == y) {
		if (y == z) s = 3;
		else s = 2;
	}
	else
	if (z == y) {
		s = 2;
	}
	else
	if (z == x) {
		s = 2;
	}
	else s = 1;
	return s;
}
