#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BUFFER 1260

int main(int argc, char** argv)
{
	FILE *GivenFile;
	char *FileARG = argv[1];
	int LineNumber = 1;
	bool Editing = true;
	char UserInput[128];
	char *Tok;

	GivenFile = fopen(FileARG, "rb+");	

	// if the given file does not exist. it creates a new file
	if(GivenFile==NULL)
	{
		GivenFile = fopen("Untitled.txt", "w+");	
	}	
	fseek(GivenFile, 0, SEEK_END);
	size_t fileSize = ftell(GivenFile);
	rewind(GivenFile);
	unsigned char* FileBuffer = malloc(fileSize);
	fread(FileBuffer, 1, fileSize, GivenFile);

	while(Editing)
	{
		fputs("$ ", stdout);
		fgets(UserInput, 128, stdin);
		Tok = strtok(UserInput, ":");
		if(strncmp(Tok, "l", 10)==0)
		{
			fwrite(FileBuffer, sizeof(char), fileSize, stdout);
		}			
	}

	fclose(GivenFile);
		
	return 0;
}
