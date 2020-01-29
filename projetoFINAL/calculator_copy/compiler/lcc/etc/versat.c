/* picoVersat */
#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "/usr/local/versat/lcc/"
#endif

#ifndef PICODIR
#define PICODIR "/usr/local/versat/pico/"
#endif

#ifndef VERILOGDIR
#define VERILOGDIR "/usr/local/bin/"
#endif

char *suffixes[] = { ".c", ".i", ".va", ".hex", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "cpp",
	"-U__GNUC__", "-D_POSIX_SOURCE", "-D__STDC__=1", "-D__STRICT_ANSI__",
	"-Dversat", "-Dpicoversat",
	"-Dunix", "-D__unix__", "-D__linux__", "$1", "$2", "$3", 0 };
char *include[] = {"-I" LCCDIR "include", 0 };
char *com[] = { LCCDIR "rcc", "-target=versat", "$1", "$2", "$3", 0 };
char *as[] = { LCCDIR "va", "$2", "$3", LCCDIR "xdict.json", 0 }; /* no $1 */
char *ld[] = { VERILOGDIR "iverilog", "-Wall", "-g2005-sv", "-DDEBUG",
	"-DINPUT=\"$2\"", "-o", "$3", "-I" PICODIR "include",
	PICODIR "src/xtop.v", PICODIR "src/xram.v",
	PICODIR "src/xctrl.v", PICODIR "src/xcprint.v",
	PICODIR "src/xaddr_decoder.v", PICODIR "src/xregf.v",
	PICODIR "testbench/xtop_tb.v", 0 };

extern char *concat(char *, char *);

int option(char *arg) {
  	if (strncmp(arg, "-lccdir=", 8) == 0) {
		include[0] = concat("-I", concat(&arg[8], "/include"));
		cpp[0] = concat(&arg[8], "/cpp");
		com[0] = concat(&arg[8], "/rcc");
		as[0] = concat(&arg[8], "/va");
		as[3] = concat(&arg[8], "/xdict.json");
	} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-pg") == 0) {
		;
	} else if (strcmp(arg, "-b") == 0) 
		;
	else if (strcmp(arg, "-g") == 0)
		;
	else if (strncmp(arg, "-ld=", 4) == 0) {
		ld[0] = &arg[4];
	} else if (strcmp(arg, "-static") == 0) {
		;
	} else
		return 0;
	return 1;
}
