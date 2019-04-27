#!/usr/bin/env python3

import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--memcheck", 
                    help="runs with valgrind to check for memory leaks",
                    action="store_true")
args = parser.parse_args()

# getting all test files
test_dir = "./tests"
test_files = [f for f in os.listdir(test_dir) if f[len(f)-7:len(f)] == "test.cc"]

# if bin directory doesn't exist, create it
if not os.path.exists("bin/"):
    os.makedirs("bin/")

# building the compile command with all test files and pre-compiled test_driver
compile_command = "g++ -o bin/test bin/test_driver.o "
for file in test_files:
    compile_command += f"tests/{file} "

# compiling test files
compile_exit_code = os.system(compile_command)

# exectuing test binary
if compile_exit_code == 0:
    if args.memcheck:
        os.system("valgrind --leak-check=yes bin/test")
    else:
        os.system("bin/test")
