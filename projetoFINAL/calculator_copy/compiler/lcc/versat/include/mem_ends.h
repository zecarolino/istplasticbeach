/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt

  Description: memory map as viewed from the xctrl block

   Copyright (C) 2014 Authors

  Author(s): Jose T. de Sousa <jose.t.de.sousa@gmail.com>
             Joao Dias lopes <joao.d.lopes91@gmail.com>

***************************************************************************** */

//Index
#define CTRL_REGF_BASE 0
#define RB 63
#define DMA_BASE 64
#define PROG_MEM_BASE 2048
#define CONF_MEM_BASE 4096
#define ENG_BASE 6144

//Control register file
#define R0 CTRL_REGF_BASE
#define R1 1
#define R2 1
#define R3 1
#define R4 1
#define R5 1
#define R6 1
#define R7 1
#define R8 1
#define R9 1
#define R10 1
#define R11 1
#define R12 1
#define R13 1
#define R14 1
#define R15 1

//DMA
#define DMA_EXT_ADDR_ADDR DMA_BASE
#define DMA_INT_ADDR_ADDR 1
#define DMA_SIZE_ADDR 1
#define DMA_DIRECTION_ADDR 1
#define DMA_STATUS_ADDR 1

//Configuration subsystem
//Memory configuration offsets
#define MEM_CONF_ITER_OFFSET 0
#define MEM_CONF_PER_OFFSET 1
#define MEM_CONF_DUTY_OFFSET 2
#define MEM_CONF_SELA_OFFSET 3
#define MEM_CONF_START_OFFSET 4
#define MEM_CONF_SHIFT_OFFSET 5
#define MEM_CONF_INCR_OFFSET 6
#define MEM_CONF_DELAY_OFFSET 7
#define MEM_CONF_RVRS_OFFSET 8
#define MEM_CONF_OFFSET 9
//ALU configuration offsets
#define ALU_CONF_SELA_OFFSET 0
#define ALU_CONF_SELB_OFFSET 1
#define ALU_CONF_FNS_OFFSET 2
#define ALU_CONF_OFFSET 3
//ALU lite configuration offsets
#define ALU_LITE_CONF_SELA_OFFSET 0
#define ALU_LITE_CONF_SELB_OFFSET 1
#define ALU_LITE_CONF_FNS_OFFSET 2
#define ALU_LITE_CONF_OFFSET 3
//MULT configuration offsets
#define MUL_CONF_SELA_OFFSET 0
#define MUL_CONF_SELB_OFFSET 1
#define MUL_CONF_LONHI_OFFSET 2
#define MUL_CONF_DIV2_OFFSET 3
#define MUL_CONF_OFFSET 4
//BS configuration offsets
#define BS_CONF_SELA_OFFSET 0
#define BS_CONF_SELB_OFFSET 1
#define BS_CONF_LNA_OFFSET 2
#define BS_CONF_LNR_OFFSET 3
#define BS_CONF_OFFSET 4

//configuration register
#define CLEAR_CONFIG_ADDR (CONF_MEM_BASE + 1023)
#define MEM0A_CONFIG_ADDR (CONF_MEM_BASE + 1024)
#define MEM0B_CONFIG_ADDR (MEM0A_CONFIG_ADDR+MEM_CONF_OFFSET)
#define MEM1A_CONFIG_ADDR (MEM0B_CONFIG_ADDR+MEM_CONF_OFFSET) 
#define MEM1B_CONFIG_ADDR (MEM1A_CONFIG_ADDR+MEM_CONF_OFFSET) 
#define MEM2A_CONFIG_ADDR (MEM1B_CONFIG_ADDR+MEM_CONF_OFFSET)
#define MEM2B_CONFIG_ADDR (MEM2A_CONFIG_ADDR+MEM_CONF_OFFSET)
#define MEM3A_CONFIG_ADDR (MEM2B_CONFIG_ADDR+MEM_CONF_OFFSET)
#define MEM3B_CONFIG_ADDR (MEM3A_CONFIG_ADDR+MEM_CONF_OFFSET)
#define ALU0_CONFIG_ADDR  (MEM3B_CONFIG_ADDR+MEM_CONF_OFFSET)
#define ALU1_CONFIG_ADDR  (ALU0_CONFIG_ADDR+ALU_CONF_OFFSET)
#define ALU_LITE0_CONFIG_ADDR  (ALU1_CONFIG_ADDR+ALU_CONF_OFFSET)
#define ALU_LITE1_CONFIG_ADDR  (ALU_LITE0_CONFIG_ADDR+ALU_LITE_CONF_OFFSET)
#define ALU_LITE2_CONFIG_ADDR  (ALU_LITE1_CONFIG_ADDR+ALU_LITE_CONF_OFFSET)
#define ALU_LITE3_CONFIG_ADDR  (ALU_LITE2_CONFIG_ADDR+ALU_LITE_CONF_OFFSET)
#define MULT0_CONFIG_ADDR (ALU_LITE3_CONFIG_ADDR+ALU_LITE_CONF_OFFSET)
#define MULT1_CONFIG_ADDR (MULT0_CONFIG_ADDR+MUL_CONF_OFFSET)
#define MULT2_CONFIG_ADDR (MULT1_CONFIG_ADDR+MUL_CONF_OFFSET)
#define MULT3_CONFIG_ADDR (MULT2_CONFIG_ADDR+MUL_CONF_OFFSET)
#define BS0_CONFIG_ADDR (MULT3_CONFIG_ADDR+MUL_CONF_OFFSET)


//Data engine
#define ENG_CTRL_REG ENG_BASE
#define ENG_STATUS_REG 1
#define ENG_FU_BASE (ENG_BASE+2**N_W) 
#define ENG_MEM_BASE ENG_BASE+2048
//Data engine: FUs
#define MEM0A ENG_FU_BASE
#define MEM0B (MEM0A+1)
#define MEM1A (MEM0B+1)
#define MEM1B (MEM1A+1)
#define MEM2A (MEM1B+1)
#define MEM2B (MEM2A+1)
#define MEM3A (MEM2B+1)
#define MEM3B (MEM3A+1)
#define ALU0 (MEM3B+1)
#define ALU1 (ALU0+1)
#define ALULITE0 (ALU1+1)
#define ALULITE1 (ALULITE0+1)
#define ALULITE2 (ALULITE1+1)
#define ALULITE3 (ALULITE2+1)
#define MULT0 (ALULITE3+1)
#define MULT1 (MULT0+1)
#define MULT2 (MULT1+1)
#define MULT3 (MULT2+1)
#define BS0 (MULT3+1)
