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
	int Count = 0;
	bool Editing = true;
	char UserInput[128];
	char *Tok;
	int Lines[100][2];
	char *FileBuffer;
	size_t ENT = 0;


	GivenFile = fopen(FileARG, "rb+");	
	

	// if the given file does not exist. it creates a new file
	if(GivenFile==NULL)
	{
		GivenFile = fopen("Untitled.txt", "w+");	
	}	

	fseek(GivenFile, 0, SEEK_END);
	size_t fileSize = ftell(GivenFile);
	FileBuffer = malloc(fileSize);
	rewind(GivenFile);
	FileBuffer = realloc(FileBuffer, fileSize+ENT);
	fread(FileBuffer, 1, fileSize, GivenFile);


	char inputSec[560];
	bool inputRun = true;
/*
	for(int i=0;i<100;i++)
	{
		if(FileBuffer[i]=='\n')
		{
			Count++;
			Lines[Count][0] = Count;
			Lines[Count][1] = i;
		}
	}

	Count = 0;
	for(int i=0;i<100;i++)
	{
		printf("%d, %d\n", Lines[i][0], Lines[i][1]);
	}
*/

	while(Editing)
	{
		fputs("$ ", stdout);
		fgets(UserInput, 128, stdin);
		Tok = strtok(UserInput, ":");
		if(strcmp(Tok, "l")==0)
		{
			fwrite(FileBuffer, sizeof(char), fileSize, stdout);
		}			
		else if(strcmp(Tok, "q")==0)
		{
			free(FileBuffer);
			fclose(GivenFile);
			exit(0);
		}
		else if(strcmp(Tok, "i")==0)
		{
			while(inputRun)
			{
				fputs(": ", stdout);
				char *ret = fgets(inputSec, 559, stdin);
// check ret and do something if null
				inputSec[559] =  '\0'; // In case fgets reads 559 bytes without a nul
                if(strncmp(inputSec, ":END:", 5)==0)
                {
                    inputRun=false;
                } else {
	                ENT = strlen(inputSec);
	                FileBuffer = realloc(FileBuffer, fileSize+ENT);
	                memcpy(FileBuffer + fileSize, inputSec, ENT);
					fileSize += ENT;
				}
			}
			inputRun=true;
		}
		else if(strcmp(Tok, "w")==0)
		{
			fwrite(FileBuffer, sizeof(char), fileSize, GivenFile);
		}
	}

	fclose(GivenFile);
		
	return 0;
}
