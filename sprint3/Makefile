# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:

CFLAGS = -c

#OBJECT FILES
OBJS = main.o test_dir.o test_gen.o test_log.o test_run.o test_string.o

#HEADER FILES
HEAD = main.hpp test_dir.hpp test_gen.hpp test_log.hpp test_run.hpp test_string.hpp

test: ${OBJS}
	${CPP} -lm ${OBJS} ${HEAD} -o test
	${CPP} progressbar.cpp -o progbar
main.o: main.cpp
test_dir.o: test_dir.cpp
test_gen.o: test_gen.cpp
test_log.o: test_log.cpp
test_run.o: test_run.cpp
test_string.o: test_string.cpp

clean:
	rm -f *.o test *~ progbar
realclean:
	rm -f *.o test *~ *.swp *.log */*.log progbar
edit:
	gedit *.hpp *.cpp &
sublime:
	sublime *.hpp *.cpp Makefile &