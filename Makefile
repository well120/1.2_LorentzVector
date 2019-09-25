FLAGS=-std=c++11 -I.

.PHONY: all test

all: test

test: .test/run

.test/run: .test/LorentzVector.o .test/main.o
	g++ ${FLAGS} $^ -o $@

.test/main.o: .test/main.cpp .test/*.hh
	g++ ${FLAGS} -c $< -o $@

.test/LorentzVector.o: LorentzVector.cpp
	g++ ${FLAGS} -c $< -o $@

run-test: test
	.test/run
