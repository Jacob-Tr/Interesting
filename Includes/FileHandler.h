struct UserFile
{
	FILE* file_pointer;
	char file_content[FILE_MAX_LINES][FILE_LINE_MAX_CHARACTERS];
};

char* GetFileLine(struct UserFile file, int line) {return file.file_content[line];}
