# Data Structures

## Todo

- Add key/value support in binary search tree so it can implement map adt, and be used to create avl tree and red-black tree classes
- Create a Makefile setup for running tests/benchmarks, compiling, etc.
- Learn what Makefile is

## Testing

Catch2 C++ unit-test framework: https://github.com/catchorg/Catch2

Tests can be running using the script `run_tests.py` which will compile 
and run all files with the form `tests/.*tests.cc`

## Naming Conventions

The Naming Conventions used in this repository are as follows:

### Code:
- Variable and function names use snake_case: (get_at, start_index)
- All container names use PascalCase: (LinkedList, HashMap)
- Abstract Data Type containers are prefixed with a capital 'I'(i): (IList, IMap)

### Files:
- All header files use the extension `.h`
- All implementation files use the extension `.cc`
- All files are named using snake_case: (linked_list.cc)
- Files containing ADT definitons have a trailing `_adt` before the file extension
- Test files are all named as `./tests/{file-being-tested}_test.cc`
