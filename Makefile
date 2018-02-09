CC = gcc
CPP = g++

cur = $(shell pwd)

head = -I $(cur)/include/\
	   -I $(cur)/include/htmlcxx/\
	   -I $(cur)/include/zlog/

test = $(cur)/test/

lib = -L $(cur)/lib\
	  -lcurl\
	  -lpthread

zlog_src = $(wildcard src/zlog/*.c)
zlog_obj = $(patsubst %.c, %.o, $(zlog_src))

src = $(wildcard src/*.cc src/htmlcxx/*.cc)
obj = $(patsubst %.cc, %.o, $(src))
main = $(cur)/src/main.o
target = spider

test_src = $(wildcard test/*.cc)
test_obj = $(patsubst %.cc, %.o, $(test_src))
test_target = $(patsubst %.cc, %.run, $(test_src))

$(target): $(obj) $(main) $(zlog_obj)
	$(CPP) -o $@ $^ $(lib)

all:

test : $(test_target)


%.run : %.o $(main) $(obj)
	$(CPP) -o $@ $^ $(lib)

%.o : %.cc
	$(CPP) -o $@ -c $< $(head)

%.o : %.cpp
	$(CPP) -o $@ -c $< $(head)

%.o : %.c
	$(CC) -o $@ -c $< $(head)

clean: 
	-rm -fr save
	-rm -fr $(target)
	-rm -fr $(main)
	-rm -fr $(obj)
	-rm -fr $(test_target)
	-rm -fr $(zlog_obj)
	-rm -fr $(test_obj)

.PHONY : clean
