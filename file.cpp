#include <string>
#include <iostream>
#include <fstream>
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
}


void writeFile(char filename[])
{
	ofstream w;
	w.open (filename);

	w.close();
}
