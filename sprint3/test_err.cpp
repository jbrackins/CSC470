#include "test_err.hpp"

using namespace std;


/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in a string and gets rid of the 
* white spaces in it.
* 
* param[in]	s - the input string
*
* returns	s - the output string without white spaces
******************************************************************************/
string trim( string s )
{
	  s.erase( remove( s.begin(),s.end(),' ' ), s.end());

	return s;
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in a string and a delimiter. It
* breaks the string into two part at the delimiter.
* 
* param[in]	s - the string 
* param[in]	delim - the delimiter
*
* returns	substrings - the structure containing two parts of the original
*				string
******************************************************************************/
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

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings to compare them.
* If the strings are of the same size and their first and last letters match,
* the function returns true, else false.
* 
* param[in]	s1 - first string 
* param[in]	s2 - second string to compare to s1
*
* returns	true - if the strings are "equal"	
* 		false - if the strings are not equal
******************************************************************************/
bool compStrs1( string s1, string s2 )
{
	auto x = s1.size();
	auto y = s2.size();

	return (( x != y ) || ( s1[0] != s2[0] ) || ( s1[x - 1] != s2[y - 1] ));	
}


/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings and checks if they
* are anagrams
* 
* param[in]	s1 - first string 
* param[in]	s2 - second string to compare to s1
*
* returns	true - if the strings are anagrams
* 		false - if the strings are not anagrams
******************************************************************************/
bool compStrs2( string s1, string s2 )
{
	sort( s1.begin(), s1.end() );
	sort( s2.begin(), s2.end() );

	return ( s1 == s2 );
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings to compare them.
* If the strings are of the same size and their first and last letters match,
* the function returns true, else false.
* 
* param[in]	s1 - first string 
* param[in]	s2 - second string to compare to s1
*
* returns	true - if the strings are "equal"	
* 		false - if the strings are not equal
******************************************************************************/
bool roundNums( string s1, string s2 )
{
	double dev = 0;
	//cout << "OH hey " << s1 << " is basically " << s2 << " right?" <<endl;
	//If the student answer is of lower precision
	if ( s1.size() > s2.size() )
	{
		//cout << "WRONGO" << endl;
		return false;
	}
	/*If the student's answer is of higher precision, then round to the same
	number of precision as the key's answer*/
	else
	{
		//Break the numbers into whole and decimal parts
		subs solution = subStrings( s1, '.' ); 
		subs diff = subStrings( s2, '.' ); 
		auto x = diff.last.size();

		//Round until the student answer is the same size as the key 
		while( x != solution.last.size() )
		{
			int y = ( diff.last[ x - 1 ] - '0' );

			if( y > 4 && ( diff.last[ x - 2 ] - '0' ) < 9 )
				diff.last[ x - 2 ] += 1;
			
			diff.last.pop_back();
			x--;
		}

		//If the rounded number does not match the key, then return false
		if(( solution.first != diff.first ) || ( solution.last != diff.last ))
		{
			//cout << "WRONGO" << endl;
			return false;
		}

		return true;
	}
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function counts the number of errors in a given 
* line.
* 
* param[in]	first - string stream from the diff file (the key part)
* param[in]	last - string stream from the diff file (the student part)
*
* returns	error - the number of errors in a given string stream
******************************************************************************/
int markError( istringstream &first, istringstream &last )
{
	int error = 0;
	int counter = 1;
	string s1, s2;
	while( first >> s1 && last >> s2 )
	{
		if(is_number(s1) || is_number(s2))
		{
			if( roundNums( s1, s2 ) != 0 )
			{
				error++;
				return error;
			}
			else
				return 0;
		}
		else if( s1 != s2 )
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
				else
					return 0;
			}
		}
		counter++;
	}
	return error;	
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function makes the diff call on the key and stude-
* nt files. The difference is stored in 'a.out'. The difference is then read in
* and the errors are detected and counted.
* 
* param[in]	file1 - name of the key file (as a string)
* param[in]	file2 - name of the student file (as a string)
*
* returns	errors - number of errors per file
******************************************************************************/
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
		
		if(markError( desc, val ))
			errors++;
		else
			return 0;
	}	

	difference.close();
	return errors;
}

/******************************************************************************
* Author: Julian Brackins
* Description: Is it a number? guess we'll find out.
* 
* param[in]	str - a string
*
* returns	true - is a number
* returns   false - is a not number
******************************************************************************/
bool is_number(const std::string& str)
{
    string::const_iterator itr = str.begin();
    while (itr != str.end() && std::isdigit(*itr)) 
    	++itr;
    return !str.empty() && itr == str.end();
}