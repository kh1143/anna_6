#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "file.h"
#include "types.h"

using namespace std;


void readFile(char* filename, char *str)
{
	int i=0;

	ifstream fin (filename, ios_base::in | ios_base::binary);
	
	if (fin.is_open())
	{   
		fin.read(str, BUF_SIZE);
	}   
	else
	{   
		return;
	}   
	
	fin.close();
}

void writeFile(char* filename, char* str)
{
	ofstream fout (filename, ios_base::out | ios_base::trunc | ios_base::binary);

	if(fout.is_open())
	{
		fout.write(str, strlen(str));
	}   
	else
	{   
		return;
	}  
	
	fout.close();
}
