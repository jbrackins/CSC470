# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:

CFLAGS = -c

#OBJECT FILES
OBJS = test.o

test: test.o
	${CPP} -lm ${OBJS} -o test
test.o: test.cpp
clean:
	rm -f *.o test
realclean:
	rm -f *.o test *~ *.swp
