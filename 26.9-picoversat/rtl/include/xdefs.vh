//
// picoVersat system definitions
//

// DATA WIDTH
`define DATA_W 32 // bits

// ADDRESS WIDTH
`define ADDR_W 15

// MODULE SELECT ADDR WIDTH
`define SEL_ADDR_W 3

// REGISTER FILE ADDRESS WIDTH


// DEBUG: USE PRINTER AND GENERATE VCD FILE
//`define DEBUG

//
// MEMORY MAP
//

`define MEM_BASE 0 //instruction and data memory
`define MEM_ADDR_W 14 //16k positions (64kB)

`define REGF_BASE 16384 //registers 0x4000
`define REGF_ADDR_W 4 //2**4 = 16 registers

`define CPRT_BASE 20480 //0x5000
`define CPRT_ADDR_W 0 //only one address

`define TRAP_BASE 32767 



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
