CC = gcc
CPP = g++

CUR = $(shell pwd)
HEAD = -I $(CUR)/include/
TEST = $(CUR)/test/

SRC = $(wildcard src/*.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

STRING = $(CUR)/test/strings_test.o
HASH = $(CUR)

TESTSRC = $(wildcard test/*.cc)
TESTOBJ = $(patsubst %.cc, %.o, $(TESTSRC))
TESTTARGET = $(patsubst %.cc, %.run, $(TESTSRC))

all:


test : $(TESTTARGET)


%.run : %.o $(OBJ)
	$(CPP) -o $@ $^

%.o : %.cc
	$(CPP) -o $@ -c $< $(HEAD)


clean: 
	-rm -fr $(OBJ)
	-rm -fr $(TESTOBJ)
	-rm -fr $(TESTTARGET)

.PHONY : clean
