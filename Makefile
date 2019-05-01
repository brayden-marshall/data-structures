SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cc .o

sources = $(wildcard tests/*_test.cc) $(wildcard tests/adt/*_test.cc)
headers = $(wildcard src/*.h) $(wildcard src/adt/*.h)
compile_prefix = g++ -Wall -Wpedantic -o bin/test bin/test_driver.o

test:  bin/test
	./bin/test

test-leaks: bin/test
	valgrind --leak-check=yes ./bin/test

bin/test: bin/test_driver.o $(sources) $(headers)
	$(compile_prefix) $(sources)

bin/test_driver.o: tests/test_driver.cc
	g++ -c -o bin/test_driver.o tests/test_driver.cc
