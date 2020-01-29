PICODIR=../../../picoversat
PICOINC=$(PICODIR)/rtl/include
N_W=5 # 2^5=32 max number of inmux inputs (from versat/verilog_src/xdefs.v)

all:: xdict.h ends.h

xdict.h: $(PICOINC)/xdefs.vh # $(PICOINC)/xctrldefs.vh $(PICOINC)/xprogdefs.vh $(PICOINC)/xregfdefs.vh
	./xdictinc $(PICODIR)/rtl/include

ends.h: mem_ends.h ends.cbc
	sed -e "s/2\*\*/2^/" < $< > ends.hbc
	cpp -DN_W=$(N_W) ends.cbc > ends.bc
	bc ends.bc > $@
	-rm ends.hbc ends.bc

clean::
	-rm -f xdict.h ends.h
