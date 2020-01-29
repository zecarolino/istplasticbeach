int var;
int main() {
	int *addr = &var;
	/* int value = 0x163;
	addr = (int*)value; */
	*addr = 12;
	return var;
}
