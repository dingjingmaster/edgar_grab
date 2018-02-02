CC = gcc
CPP = g++

cur = $(shell pwd)
head = -I $(cur)/include/\
	   -I $(cur)/include/htmlcxx/
test = $(cur)/test/

lib = -L $(cur)/lib\
	  -lcurl

src = $(wildcard src/*.cc src/htmlcxx/*.cc)
obj = $(patsubst %.cc, %.o, $(src))

test_src = $(wildcard test/*.cc)
test_obj = $(patsubst %.cc, %.o, $(test_src))
test_target = $(patsubst %.cc, %.run, $(test_src))

all:

test : $(test_target)


%.run : %.o $(obj)
	$(CPP) -o $@ $^ $(lib)

%.o : %.cc
	$(CPP) -o $@ -c $< $(head)


clean: 
	-rm -fr "./temp"
	-rm -fr $(obj)
	-rm -fr $(test_obj)
	-rm -fr $(test_target)

.PHONY : clean
