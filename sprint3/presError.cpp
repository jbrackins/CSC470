#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace boost::algorithm;


struct subs
{
	string first;
	string last;
};

void compareFiles( ifstream &solution, ifstream &fin, ifstream &difference );
bool compareStringsOne( string s1, string s2 );
bool compareStringsTwo( string s1, string s2 );
//int prezErrorCount( fstream file1, fstream file2) 
subs subStrings( string s, char delim );
bool roundNums( string s1, string s2 );
//subs 



int main()
{
	fstream difference( "a.out" );
	system( "diff -b -y -i --suppress-common-lines a.txt b.txt > a.out" );
	
	string line;
	subs dif;


	while( getline( difference, line ) )
	{
		dif = subStrings( line, '|' ); 
	}
	
	difference.close();
	return 0;
}

subs subStrings( string s, char delim )
{
	subs substrings;
	int pos = s.find_first_of( delim );
	substrings.first = s.substr( 0, pos ),
     	substrings.last = s.substr( pos + 1 );
	trim( substrings.first );
	trim( substrings.last );
	
	return substrings;
}

bool compareStringsOne( string s1, string s2 )
{
	auto x = s1.size();
	auto y = s2.size();

	return (( x != y ) || ( s1[0] != s2[0] ) || ( s1[x - 1] != s2[y - 1] ));	
}

bool compareStringsTwo( string s1, string s2 )
{
	sort( s1.begin(), s1.end() );
	sort( s2.begin(), s2.end() );

	return ( s1 == s2 );
}

bool roundNums( string s1, string s2 )
{
	if( s1.size() == s2.size() )
		return ( s1 == s2 );

	else if ( s1.size() > s2.size() )
		return false;

	else
	{
		subs solution = subStrings( s1, '.' ); 
		subs diff = subStrings( s2, '.' ); 
		auto x = diff.last.size();
		
		while( x != solution.last.size() )
		{
			int y = ( diff.last[ x - 1 ] - '0' );
			cout << "Y: " << y << endl;
		

			if( y > 4 && ( diff.last[ x - 2 ] - '0' ) < 9 )
				diff.last[ x - 2 ] += 1;
			
			diff.last.pop_back();
			x--;
		}

		return ( ( solution.first == diff.first ) && ( solution.last == diff.last ) );

	}
}

/*int prezErrorCount( fstream file1, fstream file2) 
{
	fstream difference( "a.out" );
	system( string("diff -b -y -i --suppress-common-lines" + file1 + " " + file2 " > a.out").c_str() );
	string line;
	subs dif;


	while( getline( difference, line ) )
	{
		dif = subStrings( line, '|' ); 
	}
	
	difference.close();
	return 0;
}*/
