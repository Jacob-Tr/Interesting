/*
    Copyright (C) 2021  TRACEY, Jacob

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/﻿

size_t GetStrLen(const unsigned  char* string, const size_t max_size)
{
	if(string == NULL) return 0;
	return ((size_t) strlen((char*) string));
}
int GetStrLenAsInt(const unsigned char* string, const size_t max_size) {return ((int) GetStrLen(string, max_size));}
unsigned int GetStrLenAsUInt(const unsigned char* string, const size_t max_size) {return ((unsigned int) GetStrLen(string, max_size));}

void strtoken(char* result, const unsigned char* string, unsigned int* index) 
{ 
    const unsigned char seperator = ' ';
    unsigned int length = GetStrLen(string, MAX_STRING);
    int offset = *index;
    
    do
    {
        result[*index - offset] = string[*index];
        ++*index;
    }
    while((*index < length) && (string[*index] != seperator) && ((*index - offset < length)));
    
    if((*index < length) && (string[*index] == seperator)) ++*index;

	snprintf(result, GetStrLen((unsigned char*) result, MAX_STRING) + 1, "%s", result);
}

unsigned int IsMovement(const unsigned char ch)
{
    switch(ch)
    {
		case 'e': return 1;
        case 'w': return 1;
        case 's': return 1;
        case 'a': return 1;
        case 'd': return 1;
		case 'q': return 1;
        default: return 0;
    }
}

unsigned int IsCommandDeliminator(const unsigned char ch)
{
    if(ch == '/') return 1;
    return 0;
}

unsigned int IsNumeric(const unsigned char* string, const unsigned int length)
{
    for(unsigned int i = 0; i < length; i++) 
    {
        if(string[i] == '.' || isdigit(string[i])) continue;
        else if(i == 0 && string[i] == '-') continue;
        return 0;
    }
    
    return 1;
}
