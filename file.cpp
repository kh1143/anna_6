#include <string>
#include <iostream>
#include <fstream>
<<<<<<< HEAD
using namespace std;

void readFile(char filename[])
{
	int i=0;
	char file[1024];
	
	ifstream r;
	r.open (filename);
	
//	while (r != EOF)
//	{
//		r >> file[i];
//		i++;
//	}
	
	r.close();
=======
#include <assert.h>
using namespace std;

#define BUF_SIZE 1024

void readFile(char* filename, char str[1024])
{
	int i=0;

	ifstream fin (filename, ios_base::in | ios_base::binary);
	
	if (fin.is_open())
	{   
		fin.read(str, 1024);
	}   
	else
	{   
		return;
	}   
	
	fin.close();
>>>>>>> fd78047... file I/O
}

void writeFile(char* filename, char* str, int size)
{
<<<<<<< HEAD
	ofstream w;
	w.open (filename);

	w.close();
=======
	ofstream fout (filename, ios_base::out | ios_base::trunc | ios_base::binary);

	if(fout.is_open())
	{
		fout.write(str, size);
	}   
	else
	{   
		return;
	}  
	
	fout.close();
>>>>>>> fd78047... file I/O
}
