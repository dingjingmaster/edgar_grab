CC = gcc
CPP = g++

cur = $(shell pwd)
head = -I $(cur)/include/\
	   -I $(cur)/include/htmlcxx/
test = $(cur)/test/

lib = -L $(cur)/lib\
	  -lcurl\
	  -lpthread

src = $(wildcard src/*.cc src/htmlcxx/*.cc)
obj = $(patsubst %.cc, %.o, $(src))
main = $(cur)/src/main.o
target = spider

test_src = $(wildcard test/*.cc)
test_obj = $(patsubst %.cc, %.o, $(test_src))
test_target = $(patsubst %.cc, %.run, $(test_src))

$(target): $(obj) $(main)
	$(CPP) -o $@ $^ $(lib)

all:

test : $(test_target)


%.run : %.o $(main) $(obj)
	$(CPP) -o $@ $^ $(lib)

%.o : %.cc
	$(CPP) -o $@ -c $< $(head)

%.o : %.cpp
	$(CPP) -o $@ -c $< $(head)

clean: 
	-rm -fr temp
	-rm -fr $(obj)
	-rm -fr $(main)
	-rm -fr $(target)
	-rm -fr $(test_obj)
	-rm -fr $(test_target)

.PHONY : clean
