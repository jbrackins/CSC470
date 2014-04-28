# GNU C/C++ compiler and linker:
LINK = g++

# COMPILER OPTIONS:

CFLAGS = -c  -g
CXXFLAGS = $(CFLAGS) -std=c++11

#OBJECT FILES
OBJS = main.o test_dir.o test_gen.o test_log.o test_run.o test_string.o test_menu.o test_ui.o

#HEADER FILES
HEAD = main.hpp test_dir.hpp test_gen.hpp test_log.hpp test_run.hpp test_string.hpp test_menu.hpp test_ui.hpp

test: ${OBJS}
	$(LINK) -lm ${OBJS} ${HEAD} -o test
main.o: main.cpp
test_dir.o: test_dir.cpp
test_gen.o: test_gen.cpp
test_log.o: test_log.cpp
test_run.o: test_run.cpp
test_string.o: test_string.cpp
#test_menu.o: test_menu.cpp
test_ui.o: test_ui.cpp

clean:
	rm -f *.o test *~
realclean:
	rm -f *.o test *~ *.swp *.log */*.log  *.covs *.gcno
edit:
	gedit *.hpp *.cpp &
sublime:
	sublime *.hpp *.cpp Makefile &