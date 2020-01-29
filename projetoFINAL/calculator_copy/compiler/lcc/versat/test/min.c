#  define LONG_MAX	2147483647
#  define LONG_MIN	(-LONG_MAX - 1L)
int longmin() { return LONG_MIN; }
int x() { return longmin()-1; }
int main() { return x(); }

/*
#define LONG_MIN -2147483648
int longmin() { return LONG_MIN; } // warning: unsigned operand of unary -

use 0x80000000 or example above
*/
