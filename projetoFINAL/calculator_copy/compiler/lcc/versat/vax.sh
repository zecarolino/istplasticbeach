#!/bin/bash
../../picoversat/tools/assembler/va $1.va $1.hex | tail -1
iverilog -W all -I../../picoversat/rtl/include -g2005-sv -D DEBUG ../../picoversat/rtl/src/xtop.v ../../picoversat/rtl/src/xram.v ../../picoversat/rtl/src/xctrl.v ../../picoversat/rtl/src/xcprint.v ../../picoversat/rtl/src/xaddr_decoder.v ../../picoversat/rtl/src/xregf.v ../../picoversat/rtl/testbench/xtop_tb.v -DINPUT=\"$1.hex\" -o $1
./$1
