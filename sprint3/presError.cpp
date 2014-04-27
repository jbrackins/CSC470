#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct subs
{
	string first;
	string last;
};

bool compStrs1( string s1, string s2 );
bool compStrs2( string s1, string s2 );
int prezErrorCount( string file1, string file2 ); 
subs subStrings( string s, char delim );
bool roundNums( string s1, string s2 );
int markError( istringstream &first, istringstream &last );
string trim( string s );

/*int main()
{
	string a = "a.txt";
	string b = "b.txt";
	prezErrorCount( a, b );

	return 0;
}*/

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

bool compStrs1( string s1, string s2 )
{
	auto x = s1.size();
	auto y = s2.size();

	return (( x != y ) || ( s1[0] != s2[0] ) || ( s1[x - 1] != s2[y - 1] ));	
}

bool compStrs2( string s1, string s2 )
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
		cout << diff.first << " " << diff.last << endl;
		while( x != solution.last.size() )
		{
			int y = ( diff.last[ x - 1 ] - '0' );

			if( y > 4 && ( diff.last[ x - 2 ] - '0' ) < 9 )
				diff.last[ x - 2 ] += 1;
			
			diff.last.pop_back();
			x--;
		}
		if(( solution.first != diff.first ) || ( solution.last != diff.last ))
			return false;
		return true;
	}
}

int markError( istringstream &first, istringstream &last )
{
	int error = 0;
	int counter = 1;
	string s1, s2;
	while( first >> s1 && last >> s2 )
	{
		if( s1 != s2 )
		{
			if( counter % 2 != 0 )
			{
				if(( compStrs1( s1, s2 ) || compStrs2( s1, s2 )) != 0 )
					error++;
			}
			else
			{
				if( roundNums( s1, s2 ) != 0 )
					error++;
			}
		}
		counter++;
	}
	return error;	
}

int prezErrorCount( string file1, string file2 ) 
{
	ifstream difference( "a.out" );
	system(("diff -b -y -i --suppress-common-lines " + file1 + " " + file2 + " > a.out" ).c_str());
	string line;
	subs dif;
	int errors = 0;
	
	while( getline( difference, line ) )
	{
		dif = subStrings( line, '|' ); 
		istringstream desc( dif.first );
 	        istringstream val( dif.last );
		
		errors += markError( desc, val );
	}	

	difference.close();
	return errors;
}

string trim( string s )
{
	  s.erase( remove( s.begin(),s.end(),' ' ), s.end());

	return s;
}
