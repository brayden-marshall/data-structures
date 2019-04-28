#!/usr/bin/env python3

import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--memcheck", 
                    help="runs with valgrind to check for memory leaks",
                    action="store_true")
parser.add_argument("-M", "--memcheck-verbose",
                    help="same as '-m', but adds valgrind option '-v' for error reporting",
                    action="store_true")
parser.add_argument("-o", "--omit",
                    nargs="+",
                    type=str,
                    help="omit the specified test(s)")
args = parser.parse_args()

# getting all test files
test_dirs = ["./tests", "./tests/adt"]
test_files = []
for dir in test_dirs:
    for file in os.listdir(dir):
        if file[len(file)-7:len(file)] == "test.cc":
            test_files.append(file)

# if bin directory doesn't exist, create it
if not os.path.exists("bin/"):
    os.makedirs("bin/")

# building the compile command with all test files and pre-compiled test_driver
compile_command = "g++ -o bin/test bin/test_driver.o "

# filter out files specified in args.omit
if args.omit:
    test_files = [x for x in test_files if not x in args.omit]

for file in test_files:
    compile_command += f"tests/{file} "

# compiling test files
compile_exit_code = os.system(compile_command)

# executing test binary
if compile_exit_code == 0:
    execute_command = "";
    if args.memcheck or args.memcheck_verbose:
        execute_command += "valgrind --leak-check=yes "

    if args.memcheck_verbose:
        execute_command += "-v "

    os.system(execute_command + "bin/test")
