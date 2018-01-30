CC = gcc
CPP = g++

CUR = $(shell pwd)
HEAD = -I $(CUR)/include/
TEST = $(CUR)/test/

SRC = $(wildcard src/*.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))



TESTSRC = $(wildcard test/*.cc)
TESTOBJ = $(patsubst %.cc, %.o, $(TESTSRC))
STRINGTEST = $(CUR)/test/string_test

test = $(STRINGTEST)

all:

test : $(test)

# 测试相关
$(STRINGTEST) : $(OBJ) $(TESTOBJ)
	$(CPP) -o $@ $^ $(HEAD)

%.o : %.cc
	$(CPP) -o $@ -c $< $(HEAD)


clean: 
	-rm -fr $(OBJ)
	-rm -fr $(TESTOBJ)
	-rm -fr $(test)

.PHONY : clean
