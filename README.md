# Data Structures

## Purpose

This repository is my attempt to research and implement as many data structures as I can,
while also learning to write in C++. Being able to understand data structures is a very
important computer science fundamental, and for me the only way to fully understand how
a data structure works is to implement it myself.

### Why C++ ?

Short answer: I felt like learning C++

Long answer: 

C++ forces you to pay attention to details that other high-level languages
like Python or Go will abstract away for you. I felt that having to learn all of these
details while working on data structures would give me a deeper understanding of what
is going on beneath the surface. 

I also considered using C or Rust, but I wanted to be able to implement all the data 
structures as generics, and didn't wanted to have to go through learing 
[this](https://rust-unofficial.github.io/too-many-lists/index.html) just to be able to 
write a linked list. That being said, I think it would have been equally as valuable 
to do in good ole C, and I do plan on learning Rust in the future.

## Testing

This repository uses the Catch2 C++ unit-test framework: <https://github.com/catchorg/Catch2>

Tests are run through a `Makefile`, with the commands:
- `make test`: build and runs test binary
- `make test-leaks`: runs tests with `valgrind --leak-check=yes` to check for memory leaks

## Naming Conventions

The Naming Conventions used in this repository are as follows:

### Code:
- Variable and function names use snake_case: (`get_at`, `start_index`)
- All container names use PascalCase: (`LinkedList`, `HashMap`)
- Abstract Data Type containers are prefixed with a capital 'I'(i): (`IList`, `IMap`)
- Class member variables are named with a trailing underscore (`head_`, `size_`) (except for nested classes at the moment)

### Files:
- All header files use the extension `.h`
- All implementation files use the extension `.cc`
- All files are named using snake_case: (`linked_list.cc`)
- Files containing ADT definitons have a trailing `_adt` before the file extension
- Test files are all named as `./tests/{file-being-tested}_test.cc`

## TODO

- Go through exception usage and replace with more appropriate types (all are currently `std::runtime_error`)
