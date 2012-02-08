#include "./string_functions.hpp"
#include <stdio.h>

using namespace std;

char * strup(char *s)
{
    char *p = s;
    // Convert each char
    while(*p)
    {
        if (((*p) >= 'a') && ((*p) <= 'z'))
            *p = *p -'a' + 'A';
        p++;
    }
    return s;
}

std::vector<std::string> tokenize_string(const std::string & str, const std::string & delimiters)
{   std::vector<std::string> tokens;

    // skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
       	// found a token, add it to the vector.
       	tokens.push_back(str.substr(lastPos, pos - lastPos));

       	// skip delimiters.  Note the "not_of"
       	lastPos = str.find_first_not_of(delimiters, pos);

       	// find next "non-delimiter"
       	pos = str.find_first_of(delimiters, lastPos);
    }

	return tokens;
}

std::string fgetline(FILE * fin)
{   std::string tmp_str;
    char tmp_Char;

    while((tmp_Char = fgetc(fin)) != '\n' )
    {   if (tmp_Char == EOF) return tmp_str;
        tmp_str += tmp_Char;
    }

    return tmp_str;
}

std::string trim_white_space(const std::string & str)
{   string tmp_str;
    string::size_type pos;

    // Leading
    if ((pos = str.find_first_not_of(" \t")) != string::npos)
        tmp_str = str.substr(pos);
    else
        tmp_str = str;

    // Trailing
    if ((pos = tmp_str.find_last_not_of(" \t")) != string::npos)
        tmp_str.erase(pos + 1);

    return tmp_str;
}
