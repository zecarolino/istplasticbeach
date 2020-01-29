#include "versat.h"

static int base = VERSAT_MEM0A, versatFu = VERSAT_FU;

Versat config1 = { { 2000, 1, 1, 0, 0, 1, 1, 0, 0, } };

int main() {
	Versat *versatFU = (Versat*)base;
	VersatDE *versatDE = (VersatDE*)versatFu;
	*versatFU = config1;
	return 0;
}
