#ifndef TEST_GEN_CPP_INCLUDED
#define TEST_GEN_CPP_INCLDED

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
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
void generatetestcases();
void generatetestcasesmenu(bool &doubles, bool &lesserThanAmount, 
                           bool &greaterThanAmount, double &min, double &max, 
                           int &amountToGenerate, int &filesToMake);
void pregenerateclean();
void generateanswers();

#endif