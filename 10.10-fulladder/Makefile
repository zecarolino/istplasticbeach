fulladder: fulladder.v top.v fulladder_tb.v
	iverilog -o  fulladder fulladder.v top.v fulladder_tb.v
	./fulladder

clean: 
	rm -f fulladder *~ *.vcd

.PHONY: clean all
