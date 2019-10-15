carrylookahead: BlocoA.v BlocoB.v BlocoC.v top.v carrylookahead_tb.v
	iverilog -o  carrylookahead BlocoA.v BlocoB.v BlocoC.v top.v carrylookahead_tb.v
	./carrylookahead

clean: 
	rm -f carrylookahead *~ *.vcd

.PHONY: clean all
