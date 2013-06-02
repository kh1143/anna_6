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

char* readZip(char* filename, char *bit, int *bit_len)
{
	FILE* file;
	char* treeStr;
	int len;

	file = fopen(filename, "r+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return NULL;
	}

	if (fread(&len, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot Read size len." << endl;
		fclose (file);
		return NULL;
	}

	treeStr = new char[len + 1];

	if (fread(treeStr, len, 1, file) == -1)
	{
		cout << "Failed: Cannot Read size treeStr." << endl;
		fclose (file);
		return NULL;
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
	
	return treeStr;
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

bool writeZip(char* filename, char *treeStr, char* bit, int bit_len)
{
	FILE* file;
	int len;

	file = fopen(filename, "w+");
	if(!file)
	{
		cout << "Cannot Open File:" << filename<<endl;
		return false;
	}

	len = strlen(treeStr);
	
	if (fwrite(&len, sizeof(int), 1, file) == -1)
	{
		cout << "Failed: Cannot write len." << endl;
		fclose (file);
		return false;
	}
	if (fwrite(treeStr, len, 1, file) == -1)
	{
		cout << "Failed: Cannot write treeStr." << endl;
		fclose (file);
		return false;
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

