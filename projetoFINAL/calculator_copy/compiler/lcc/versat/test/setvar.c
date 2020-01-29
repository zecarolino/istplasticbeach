/* uses more #14 clocks than set.c because it spills R4: push#6 + pop#8 */
void setvar(int value, int *addr) { *addr = value; }
int var;
int main() { setvar(13, &var); return var; }
