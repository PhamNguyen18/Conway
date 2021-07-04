 .POSIX:
 .SUFFIXES:
PROG = conway 
CC = g++
CFLAGS = -std=c++17 -Wall -g -O2
LDLIBS = -lm
OBJS = conway.o conway_funcs.o

all: $(PROG) 
$(PROG): $(OBJS) 
	$(CC) -o conway conway.o conway_funcs.o $(LDLIBS)
conway.o: conway.cpp conway_funcs.h
	$(CC) $(CFLAGS) -c conway.cpp
conway_funcs.o: conway_funcs.cpp conway_funcs.h
	$(CC) $(CFLAGS) -c conway_funcs.cpp
clean:
	rm -f $(PROG) $(OBJS) 
