
  C compiler for picoVersat

Install the following software under the same directory:

1) install iverilog:

	a) 'git clone https://github.com/steveicarus/iverilog'

	b) sudo apt install autoconf gperf

	c) in iverilog/ do 'sh autoconf.sh; ./configure; make; sudo make install'

2) install picoversat:

	a) https://bitbucket.org/jjts/picoversat.git'

	b) change "./program.hex" to `INPUT in picoversat/rtl/src/xram.v


3) install lcc:

	a) install at the directory level as picoversat or change 'lcc/versat/Makefile' accordingly

	b) https://goncalosantos0@bitbucket.org/goncalosantos0/lcc.git

	c) in lcc/ do 'mkdir obj' and 'make all' to generate lcc.

	d) in lcc/versat/ link xtop.vcd to /dev/null to avoid generating core.

	e) in lcc/versat/ do 'make test' to run regression tests

	f) to install do 'make install' in lcc/ and lcc/versat/

4) run example:

	a) compile code: 'lcc example.c -o example'

	b) run compiled code: './example'

Gonçalo Santos, 2019
