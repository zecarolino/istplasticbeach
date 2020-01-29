.SUFFIXES: .hex .va .vvp .vah
PICODIR=../../../picoversat
CALCDIR=../../../peripherals
#PICODIR=../../picoversat\.ee36325
#PICODIR=../../picoversat.4a9c764
PICOSRC=$(PICODIR)/rtl/src
PICOINC=$(CALCDIR)/includes
LCCDIR=..
INSTDIR=/usr/local/versat/lcc/
VERILOG=iverilog -W all -o $@ -I$(PICOINC) -g2005-sv -D DEBUG \
	$(CALCDIR)/src/xtop.v $(CALCDIR)/src/xram.v \
	$(PICODIR)/rtl/src/xctrl.v $(PICODIR)/rtl/src/xcprint.v \
	$(CALCDIR)/src/x7segments.v $(CALCDIR)/src/xbutton_controler.v \
	$(CALCDIR)/src/xhex2disp.v $(CALCDIR)/src/xregister.v \
	$(CALCDIR)/src/xdebouncer.v \
	$(CALCDIR)/src/xaddr_decoder.v $(PICODIR)/rtl/src/xregf.v \
	$(CALCDIR)/testbench/xtop_tb.v
ASM=$(PICODIR)/tools/assembler/va
VCC=($(LCCDIR)/obj/cpp -D$(DEFINE) -Iinclude | $(LCCDIR)/obj/rcc -target=$(TARGET))
TARGET=versat
DEFINE=$(TARGET)
DBG=| tail -1
TEST=*# 'make test TEST=hello' to run a single test
TESTS=test/$(TEST).out



	#$(CALCDIR)/src/xvgacontroller.v $(CALCDIR)/src/xdebouncer.v \
	$(CALCDIR)/src/xvideoencoder.v $(CALCDIR)/src/xvideomemory.v \
	$(CALCDIR)/src/xpixelrom.v \

all:: example add test

xdict.json: $(PICOINC)/xdefs.vh # $(PICOINC)/xctrldefs.vh $(PICOINC)/xprogdefs.vh $(PICOINC)/xregfdefs.vh
	$(PICODIR)/tools/xdictgen $(PICOINC)

.c.va:
	$(VCC) < $< > $@

.va.hex: xdict.json
	$(ASM) $< $@ | tee $*.vah

%:%.hex
	cp $< program.hex
	$(VERILOG)
	./$@

%:%.c xdict.json
	-$(MAKE) $(MFLAGS) -C .. rcc
	$(VCC) < $< > $*.va
	$(ASM) $*.va $*.hex $(DBG)
	cp $*.hex program.hex
	$(VERILOG)
	./$@

%:%.va xdict.json
	$(ASM) $< $*.hex
	cp $*.hex program.hex
	$(VERILOG)
	./$@

install:: xdict.json
	-$(MAKE) $(MFLAGS) -C include
	cp -r include va xdict.json $(INSTDIR)

	#-ln -s /dev/null xtop.vcd
test:: clean
	-rm -f xtop.vcd
	-if [ ! -d ../obj ]; then mkdir ../obj; fi
	-$(MAKE) $(MFLAGS) -C .. cpp
	-$(MAKE) $(MFLAGS) -C .. rcc
	-for i in $(TESTS); do f=test/`basename $$i .out`; echo -n "$$f "; rm -f $$f; ($(MAKE) $(MFLAGS) $$f > test/`basename $$i .out`.log); ./$$f | diff - $$i; done
	@echo done.

testoutput:: clean
	@read -p "overwrite the outputs of the tests!!! " x
	sleep 3
	-for i in test/*.out; do f=test/`basename $$i .out`; echo -n "$$f "; rm -f $$f; ($(MAKE) $(MFLAGS) $$f > /dev/null); ./$$f > $$i; done
	@echo done.

clean::
	-$(MAKE) $(MFLAGS) -C include clean
	-rm -f xdict.json *.hex *.vah *.vvp a.out rom.v xtop.vcd program.va test/*.va test/*.vah test/*.hex test/*.log
	-if [ `ls *.c | wc -l` -gt 0 ]; then for i in *.c; do rm -f `basename $$i .c`.va; done; fi
	-rm -f `file * | grep 'vvp script' | awk -F: '{ print $$1}'` a.out
	-rm -f `file test/* | grep 'vvp script' | awk -F: '{ print $$1}'` a.out

backup:: clean
	(cd ..; tar zcf lcc_versat-`date +%d%b%g-%Hh%M`.tgz versat/ src/versat.md src/pico.md src/bind.c src/c.h src/main.c src/types.c src/expr.c etc/versat.c etc/lcc.c makefile -C ../tese/intro Thesis_Development.tex Thesis_StateOfTheArt.tex Thesis_Tests.tex Thesis_Results.tex Thesis_Conclusions.tex)
