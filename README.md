# MyLang

A scripting language and bytecode virtual machine built from scratch in C++.
No libraries. Just a handwritten lexer, parser, compiler, and VM.

## Status
- [x] Lexer
- [x] Parser
- [x] Bytecode compiler
- [x] Virtual machine
- [ ] Variables and control flow
- [ ] Functions
- [ ] Debugging tools (disassembler or REPL)

## How it works
Source code goes through a 4-stage pipeline:

Source → Lexer → Parser → Compiler → Bytecode → VM → Output

- **Lexer** — reads raw text and breaks it into tokens
- **Parser** — builds an Abstract Syntax Tree (AST) from tokens
- **Compiler** — walks the AST and emits bytecode instructions
- **VM** — executes the bytecode on a stack-based virtual machine

## Build & Run
```bash
g++ src/main.cpp src/lexer/lexer.cpp src/parser/parser.cpp src/compiler/compiler.cpp src/vm/vm.cpp -o lang
./lang
```

## Example
// arithmetic expressions currently supported
12 + 3 * (45 - 6)  // outputs 129

## Project Structure

```
MyLang/
├── src/
│   ├── lexer/
│   │   ├── lexer.h
│   │   └── lexer.cpp
│   ├── parser/
│   │   ├── parser.h
│   │   └── parser.cpp
│   ├── compiler/
│   │   ├── compiler.h
│   │   └── compiler.cpp
│   ├── vm/
│   │   ├── vm.h
│   │   └── vm.cpp
│   └── main.cpp
├── .gitignore
└── README.md
```

## Goals
- Fast execution via stack-based bytecode
- Clean, readable syntax
- Built-in debugging tools (disassembler or REPL)

## Progress
Building this over the summer as a 1st year CS student.
Documenting the process as I go.