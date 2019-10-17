multcomb: halfadder.v top.v mult_tb.v
	iverilog -o  multcomb halfadder.v top.v mult_tb.v
	./multcomb

clean: 
	rm -f multcomb *~ *.vcd

.PHONY: clean all
