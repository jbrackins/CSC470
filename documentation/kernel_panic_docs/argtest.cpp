#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool verifyArg(string file);
	
int main(int argc, char *argv[])
{
	string file = argv[1];
	verifyArg(argv[1]);

}

bool verifyArg(string file)
{
	ifstream fin;

	int found = file.find_last_of(".");
	if(found == -1)
	{
		cout<<"Invalid: File doesn't have an extension"<<endl;
		return false;
	}
	fin.open(file.c_str());
	if(!fin)
	{
		cout<<"Invalid: File doesn't exist or couldn't be opened"<<endl;
		return false;
	}
	return true;
}
