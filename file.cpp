#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "file.h"
#include "types.h"

using namespace std;


bool readFile(char* filename, char *str)
{
	FILE* file;

	file = fopen(filename, "r+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return false;
	}
	
	if (fread(str, BUF_SIZE, 1, file) == -1)
	{
		cout << "Failed: Cannot Read." << endl;
		fclose (file);
		return false;
	}
	fclose (file);
	return true;
}

CodeTable* readZip(char* filename, int *size, char *bit, int *bit_len)
{
	FILE* file;
	CodeTable* ct;

	file = fopen(filename, "r+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return false;
	}

	if (fread(size, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot Read size." << endl;
		fclose (file);
		return false;
	}

	ct = new CodeTable[*size];

	for (int i = 0; i<*size; i++)
	{
		int len;
		
		if (fread(&ct[i], sizeof(CodeTable), 1, file) == -1)
		{
			cout << "Failed: Cannot Read size CodeTable." << endl;
			fclose (file);
			return NULL;
		}
		if (fread(&len, sizeof(int), 1, file) == -1)
		{
			cout << "Failed: Cannot Read size len." << endl;
			fclose (file);
			return NULL;
		}
		ct[i].code = new char[len+1];
		if (fread(ct[i].code, len, 1, file) == -1)
		{
			cout << "Failed: Cannot Read size CodeTable." << endl;
			fclose (file);
			return NULL;
		}
	}
	
	if (fread(bit_len, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot Read str." << endl;
		fclose (file);
		return NULL;
	}
	if (fread(bit, *bit_len, 1, file) == -1)
	{
		cout << "Failed: Cannot Read str." << endl;
		fclose (file);
		return NULL;
	}
	fclose (file);
	
	return ct;
}


bool writeFile(char* filename, char* str)
{
	FILE* file;

	file = fopen(filename, "w+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return false;
	}

	if (fwrite(str, strlen(str), 1, file) == -1)
	{
		cout << "Failed: Cannot write str." << endl;
		fclose (file);
		return false;
	}
	fclose (file);

	return true;
}

bool writeZip(char* filename, CodeTable *ct, int size, char* bit, int bit_len)
{
	FILE* file;

	file = fopen(filename, "w+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return false;
	}

	if (fwrite(&size, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot write size." << endl;
		fclose (file);
		return false;
	}
	
	for (int i = 0; i<size; i++)
	{
		int len = strlen(ct[i].code);
		
		if (fwrite(&ct[i], sizeof(CodeTable), 1, file) == -1)
		{
			cout << "Failed: Cannot write CodeTable." << endl;
			fclose (file);
			return false;
		}
		if (fwrite(&len, sizeof(int), 1, file) == -1)
		{
			cout << "Failed: Cannot write len." << endl;
			fclose (file);
			return false;
		}
		if (fwrite(ct[i].code, len, 1, file) == -1)
		{
			cout << "Failed: Cannot write CodeTable." << endl;
			fclose (file);
			return false;
		}
	}
	
	if (fwrite(&bit_len, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot write bit_len." << endl;
		fclose (file);
		return false;
	}
	if (fwrite(bit, bit_len, 1, file) == -1)
	{
		cout << "Failed: Cannot write str." << endl;
		fclose (file);
		return false;
	}
	fclose (file);

	return true;
}

