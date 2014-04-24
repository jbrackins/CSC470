#ifndef TEST_RUN_CPP_INCLUDED
#define TEST_RUN_CPP_INCLDED

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <stdio.h>
#include <cstring>

#include <fstream>
#include <time.h>
#include <vector>
#include <sstream>
// QQQ!!! Alex : added
#include <unistd.h>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

int Event_REDIRECT(const char *commandline);
int runtests(std::string  prog, std::string specifictestcase);
int filesequal(std::string  file1name, std::string file2name);
void cleanup();
void progbar(int kill_pid, int runtime, std::string progname);


#endif
