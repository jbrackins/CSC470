# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:

CFLAGS = -c

#OBJECT FILES
OBJS = test.o

#HEADER FILES
HEAD = header.h test.h test_dir.h test_crit.h test_gen.h test_string.h

test: test.o
	${CPP} -lm ${OBJS} ${HEAD} -o test
test.o: test.cpp
clean:
	rm -f *.o test *~
realclean:
	rm -f *.o test *~ *.swp *.log */*.log
edit:
	gedit *.h *.cpp &
