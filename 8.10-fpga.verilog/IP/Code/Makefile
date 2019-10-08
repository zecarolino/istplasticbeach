adder: xadder.v xadder_tb.v
	iverilog -o adder  xadder.v xadder_tb.v
	./adder

clean: 
	rm -f adder *~ *.vcd

.PHONY: clean all
