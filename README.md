# [MyLang]

A scripting language and bytecode virtual machine built from scratch in C++.
No libraries. Just a handwritten lexer, parser, compiler, and VM.

## Status
- [x] Lexer
- [x] Parser
- [ ] Bytecode compiler
- [ ] Virtual machine

## How it works
Source code goes through a 4-stage pipeline:

Source → Lexer → Parser → Compiler → Bytecode → VM → Output

- **Lexer** — reads raw text and breaks it into tokens
- **Parser** — builds an Abstract Syntax Tree (AST) from tokens
- **Compiler** — walks the AST and emits bytecode instructions
- **VM** — executes the bytecode on a stack-based virtual machine

## Build & Run
```bash
g++ src/main.cpp src/lexer.cpp src/parser.cpp -o lang
./lang
```

## Example
```
// coming soon — will update as the language develops
```

## Project Structure
```
src/
├── main.cpp
├── lexer.h
├── lexer.cpp
├── parser.h
└── parser.cpp
``` 

## Goals
- Fast execution via stack-based bytecode
- Clean, readable syntax
- Built-in debugging tools (disassembler or REPL)

## Progress
Building this over the summer as a 1st year CS student.
Documenting the process as I go.