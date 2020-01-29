//
// picoVersat system definitions
//

// DATA WIDTH
`define DATA_W 32 // bits

// ADDRESS WIDTH
`define ADDR_W 11

// MODULE SELECT ADDR WIDTH
`define SEL_ADDR_W 3

// REGISTER FILE ADDRESS WIDTH


// DEBUG: USE PRINTER AND GENERATE VCD FILE
//`define DEBUG

//
// MEMORY MAP
//

`define MEM_BASE 0 //instruction and data memory
`define MEM_ADDR_W 10 //512 positions (2kB)
`define STACK_BASE 1024
`define STACK_ADDR_W 4 //2**4 = 16 address

`define REGF_BASE 1024 //registers 0x4000
`define REGF_ADDR_W 4 //2**4 = 16 registers

`define CPRT_BASE 1200 //0x5000
`define CPRT_ADDR_W 0 //only one address

`define MULT_BASE 1240 //0x5000
`define MULT_ADDR_W 2 //only one address

`define DIV_BASE 1264 //0x5000
`define DIV_ADDR_W 3 //only one address

`define SEG7_BASE 1480 //registers 0x4000
`define SEG7_ADDR_W 2 //2**2 = 4 registers

`define BUTT_BASE 1600 //registers 0x4000
`define BUTT_ADDR_W 2 //2**2 = 4 registers

`define VGA_BASE 1640
`define VGA_ADDR_W 1

`define NO_EXT 1

`define TRAP_BASE 2047

// Instruction width 
`define INSTR_W 32

// Instruction fields
`define OPCODESZ 4
`define IMM_W 28

`define DELAY_SLOTS 1

// Instruction codes

// arithmetic
`define addi 0
`define add 1
`define sub 2
//logic
`define shft 3
`define and 4
`define xor 5

// load / store
`define ldi 6
`define ldih 7
`define rdw 8
`define wrw 9
`define rdwb 10
`define wrwb 11

// branch
`define beqi 12
`define beq 13
`define bneqi 14
`define bneq 15
