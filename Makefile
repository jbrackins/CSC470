# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:

CFLAGS = -c

#OBJECT FILES
OBJS = grade.o

grade: grade.o
	${CPP} -lm ${OBJS} -o grade
grade.o: grade.cpp
clean:
	rm -f *.o grade *~
realclean:
	rm -f *.o grade *~ *.swp hello
