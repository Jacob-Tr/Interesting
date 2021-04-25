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
