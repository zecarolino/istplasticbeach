#assembly programs
TESTS_DIR := ../tests
#default test
test := hello_world

#rtl files
INCLUDE_DIR := ../peripherals/includes
SRC_PICOVERSAT_DIR := ../picoversat/rtl/src
SRC_CALCULATOR_DIR := ../peripherals/src

XDEFS := $(wildcard $(INCLUDE_DIR)/*.vh)
SRC_PICOVERSAT := $(SRC_PICOVERSAT_DIR)/xcprint.v $(SRC_PICOVERSAT_DIR)/xctrl.v $(SRC_PICOVERSAT_DIR)/xregf.v 
#SRC_CALCULATOR := $(SRC_CALCULATOR_DIR)/xtop.v $(SRC_CALCULATOR_DIR)/xram.v $(SRC_CALCULATOR_DIR)/x7segments.v \
	$(SRC_CALCULATOR_DIR)/xbutton_controler.v $(SRC_CALCULATOR_DIR)/xhex2disp.v $(SRC_CALCULATOR_DIR)/xregister.v \
	$(SRC_CALCULATOR_DIR)/xdebouncer.v $(SRC_CALCULATOR_DIR)/xaddr_decoder.v
SRC_CALCULATOR := $(wildcard $(SRC_CALCULATOR_DIR)/*.v) 
TB := ../peripherals/testbench/xtop_tb.v


#icarus verilog
VC = iverilog
CFLAGS = -W all -I$(INCLUDE_DIR) -g2005-sv -D DEBUG

all: a.out
	./a.out

a.out: $(SRC) firmware $(XDEFS) $(TB)
	$(VC) $(CFLAGS) $(SRC_PICOVERSAT) $(SRC_CALCULATOR) $(TB)

firmware:
	make -C $(TESTS_DIR)/$(test)
	cp $(TESTS_DIR)/$(test)/*.hex .

clean: 	
	@rm -f *#
	@rm -f *~ 
	@rm -f *.vcd
	@rm -f *.hex
	@rm -f xtop
	@rm -f *.out

.PHONY: all clean firmware
