# PATHS
VA := ../../picoversat/tools/assembler/va
INCLUDE_DIR := ../../peripherals/includes

all: program.hex

# assemble program
program.hex: program.va xdict.json
	$(VA) program.va program.hex

xdict.json: ../../peripherals/includes/xdefs.vh
	../../tools/xdictgen $(INCLUDE_DIR)


clean:
	@rm -f xdict.json *# *~ program.hex

.PHONY: all clean
