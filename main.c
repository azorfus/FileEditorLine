/*
 *	Writer: Azorfus
 *	Redistributable Code
 *	Under Development!
 *
 */
#include <stdio.h>
//#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BUFFER 1260

FILE* GivenFile;
int LineNumber = 1;
bool Editing = true;
char UserInput[128];
char* Tok;
int Lines[100][2];
char* FileBuffer;
size_t fileSize;
// size of user input string
size_t ENT = 0;

void Read_BUFF()
{
	fseek(GivenFile, 0, SEEK_END);
	fileSize = ftell(GivenFile);
	FileBuffer = malloc(fileSize);
	rewind(GivenFile);
	FileBuffer = realloc(FileBuffer, fileSize + ENT);
	fread(FileBuffer, 1, fileSize, GivenFile);
}

int main(int argc, char** argv)
{
	char* FileARG = argv[1];
	if (FileARG != NULL)
	{
		GivenFile = fopen(FileARG, "w+");
		if (GivenFile == NULL)
		{
			GivenFile = fopen("untitled", "w+");
		}
	}
	// if the given file does not exist. it creates a new file
	else
	{
		GivenFile = fopen("untitiled", "w+");
	}

	// reading the contents of the file onto FileBuffer

	Read_BUFF();

	char inputSec[560];
	bool inputRun = true;
	int I = 0;

	// Checking if the FileBuffer is NULL to avoid memory corruption
	if (FileBuffer != NULL)
	{
		// storing newline character's index with the line number for later inserts
		int Count = 1;
		int prev;
		Lines[0][0] = 1;
		Lines[0][1] = 0;
		for (int i = 0; i < fileSize; i++)
		{
			if (FileBuffer[i] != '\n' && FileBuffer[i] != '\0') continue; // ignore this iteration

			Lines[Count][0] = i + 1;
			Lines[Count - 1][1] = i - Lines[Count - 1][0];
			if (Lines[Count - 1][1] == -1)
			{
				Lines[Count - 1][1] = 0;
			}
			Count++;
			I = Count;
		}

		Lines[Count - 1][1] = fileSize - 1 - Lines[Count - 1][0];

		Count = 0;
	}



	while (Editing)
	{
		fputs("*", stdout);
		fgets(UserInput, 128, stdin);
		Tok = strtok(UserInput, ";");
		if (strcmp(Tok, "l") == 0)
		{
			fwrite(FileBuffer, sizeof(char), fileSize, stdout);
		}
		else if (strcmp(Tok, "q") == 0)
		{
			if (GivenFile != NULL)
			{
				fclose(GivenFile);
			}
			exit(0);
		}
		else if (strcmp(Tok, "a") == 0)
		{
			char* temp = "";
			size_t tempsize = strlen(temp);
			while (inputRun)
			{
				fputs(": ", stdout);
				char* ret = fgets(inputSec, 559, stdin);
				// check ret and do something if null
				inputSec[559] = '\0'; // In case fgets reads 559 bytes without a nul
				if (strncmp(inputSec, ":END:", 5) == 0)
				{
					memcpy(FileBuffer + fileSize, temp, ENT);
					fileSize += tempsize;
					inputRun = false;
				}
				else if (strncmp(inputSec, ":CNL:", 5) == 0)
				{
					temp = "";
					inputRun = false;
				}
				else {
					ENT = strlen(inputSec);
					FileBuffer = realloc(FileBuffer, fileSize + ENT);
					// copying the user input into the FileBuffer
					memcpy(temp + tempsize, inputSec, ENT);
					tempsize += ENT;
				}
			}
			inputRun = true;
		}

		else if (strcmp(Tok, "w") == 0)
		{
			fwrite(FileBuffer, sizeof(char), fileSize, GivenFile);
			printf("[%ld] bytes written to file.\n", strlen(FileBuffer));
		}
		else if (strcmp(Tok, "i") == 0)
		{
			int LNO = 0;
			bool found;
			scanf("%d", &LNO);
			for (int i = 0; i < 100; i++)
			{
				if (LNO == Lines[i][0])
				{
					printf("FOUND at index value [%d]\n", Lines[i][1]);
				}
				else
				{
					printf("Not Found!\n");
					found = false;
				}
				if (found == true)
				{

				}
			}

		}
		else if (strcmp(Tok, "r") == 0)
		{
			int LINEchsn;
			fputs(": ", stdout);
			scanf("%d", &LINEchsn);


			int INDEXchsn, INDEXend;

			if (LINEchsn >= 1 || LINEchsn < I)
			{
				LINEchsn -= 1;
				INDEXchsn = Lines[LINEchsn][0];
				INDEXend = Lines[LINEchsn + 1][0];
			}
			else
			{
				printf("Line does not exist!\n");
				break;
			}

			char* lineBeginning = FileBuffer + INDEXchsn - 1;
			//printf("%.*s", Lines[LINEchsn+1][1]-INDEXchsn, lineBeginning);

			int count = 0;
			INDEXend += 1;

			for (int i = INDEXchsn; i < INDEXend; i++)
			{
				count++;
			}

			int lineLength = count;
			//printf("Line: %.*s, Length: %d\n", lineLength, lineBeginning, lineLength);

			printf("fileSize: %ld\nlineBeginning - FileBuffer: %ld\nlineLength: %d\n", fileSize, (lineBeginning - FileBuffer), lineLength);
			printf("%ld\n", fileSize - (lineBeginning + lineLength - FileBuffer));

			memmove(lineBeginning, lineBeginning + lineLength, fileSize - lineLength - INDEXchsn);
			//			FileBuffer = realloc(FileBuffer, fileSize - lineLength);

		}

		else if (strcmp(Tok, "n") == 0)
		{
			for (int i = 0; i < 100; i++)
			{
				if (i == I)
				{
					break;
				}

				printf("%d - %d, %d\n", i, Lines[i][0], Lines[i][1]);
			}

		}
		else if (strcmp(Tok, "o") == 0)
		{
			char FILENAME[26];
			fputs(": ", stdout);
			fgets(FILENAME, 26, stdin);
			for (int i = 0; i < 26; i++)
			{
				if (FILENAME[i] == '\n')
				{
					FILENAME[i] = '\0';
				}
			}
			GivenFile = fopen(FILENAME, "r+");
			if (GivenFile == NULL)
			{
				fputs("Enter a valid file\n", stdout);
			}
			else
			{
				fputs("File Loaded.\n", stdout);
				Read_BUFF();

			}
		}
	}



fclose(GivenFile);


	return 0;
}
