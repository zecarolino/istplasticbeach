" Vim syntax file
" Language:	picoVersat Assembler
" Maintainer:	Gonçalo Santos
" Last change:	2018 Oct 31
"

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

syn case ignore

" Partial list of register symbols
syn keyword versatReg	RA RB RC R0 R1 R2 R3 R4 R5 R6 R7 R8 R9
syn keyword versatReg	R10 R11 R12 R13 R14 R15

" picoVersat opcodes
syn keyword versatOpcode add addi shft sub and xor ldi ldih
syn keyword versatOpcode rdw wrw rdwb wrwb beq beqi bneq bneqi
syn keyword versatOpcode nop wrc
syn keyword versatOpcode "\.memset"

" Valid labels
syn match versatLabel		"^[a-z_?.][a-z0-9_?.$]*$"
syn match versatLabel		"^[a-z_?.][a-z0-9_?.$]*\s"he=e-1
syn match versatLabel		"^\s*[a-z_?.][a-z0-9_?.$]*:"he=e-1

" Various number formats
syn match versatNumber		"[+-]\?\d\+"
syn match versatHex		"0x\x\+"

" Special items for comments
syn keyword versatTodo		contained TODO FIXME XXX

" Comments
syn match versatInclude	display "^#\s*include\s*\"[^"]*\"" contains=versatLabel
syn match versatInclude		"^#!.*$"
syn match versatLine		"^#line"
syn match versatComment		"#.*$" contains=versatTodo,versatInclude,versatLine

syn case match

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_versat_syntax_inits")
  if version < 508
    let did_versat_syntax_inits = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif

  HiLink versatComment		Comment
  HiLink versatTodo		Todo
  HiLink versatNumber		Number
  HiLink versatHex		Number
  HiLink versatReg		Operator
  HiLink versatInclude		Include
  HiLink versatPreProc		Special
  HiLink versatOpcode		Statement
  HiLink versatLabel		Type
  delcommand HiLink
endif

let b:current_syntax = "versat"

" vim: ts=8 sw=2
