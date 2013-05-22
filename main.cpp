#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "list.h"
#include "file.h"
#include "tree.h"
#include "huffman.h"
#include "types.h"

using namespace std;

void verifyId(string id);
void clearScreen();
int getMenuSelection ();
string getFileExtension(string filename);
string getFileWithoutExtension(string filename);
void zipFile (string inputFile, string outputFile);
void unzipFile (string inputFile, string outputFile);


std::string STUDENT_ID="2011314866";


int main(int argc, char const *argv[])
{
	char str[BUF_SIZE] = {0,};
	List* list = createList();
	Tree* tree = createTree();
	int tablesize;
	

	verifyId (STUDENT_ID);
	clearScreen();

	readFile("test", str);
	cout << str<<endl;

	MakeTable(list, str);
	displayList(list);
	tablesize = getListSize(list);

	
/*//	< sort test >

	SortTable(chlist);
	cout << "after sorted"<<endl;
	displayList(chlist);
//*/


//	<Huffman Tree Test>

	MakeHuffmanTree(tree, list);
	displayList(list);
	cout << "htree size: " << tree->size<<endl;
	cout << "total lenth : "<< strlen(str) << endl;
	cout << "htree data: ";
	displayNode(getTreeNode(tree));
	cout << endl;
//*/

	CodeTable* codetable = new CodeTable[tablesize];

	HuffmanEncode(tree, codetable);

	displayCode(codetable, tablesize);
	char code[BUF_SIZE*CODE_BUF]={0,};
	
	EncodingFile(codetable, tablesize, str, code);
	cout << code <<endl;

	char decode[BUF_SIZE];
	DecodingFile(codetable, tablesize, code, decode);
	cout << decode <<endl;

	writeFile("test.zip", code);

	char ptreestr[BUF_SIZE]={0,};
	TreeConvertToParenthesisNotaiton(tree, ptreestr);
	cout << ptreestr<<endl;
	
	while (true)
	{
		int selection= getMenuSelection();

		if (selection==3) break; // quit the program

		while (true)
		{
			cout << "Type the name of the file that you want to use" <<endl;
			string inputFile;
			cin >> inputFile;

			if (selection==1) // zip
			{
				zipFile (inputFile, inputFile+".zip");
				break;

			}else if (getFileExtension(inputFile) == "zip") // unzip
			{
				unzipFile (inputFile, getFileWithoutExtension(inputFile));
				break;

			}
			else
			cout <<"Invalid input file"<<endl;
			}
		cout <<endl;
	}
	return 0;
}




// SOME HELPER FUNCTIONS
void verifyId(string id)
{
    if (id=="PUT ONLY YOUR ID HERE")
    {
        cout << "\nInsert your ID first"<<endl;
        exit(1);
    }
}

void clearScreen()
{
    cout << string( 100, '\n' );
}

string getFileExtension(string filename)
{
	int idx = filename.rfind('.');
	if(idx == std::string::npos)
	{
		// nothing found
		return "";
	}
	//else
	return filename.substr(idx+1);
}

string getFileWithoutExtension(string filename)
{
	int idx = filename.rfind('.');
	if(idx == std::string::npos)
	{
		// nothing found
		return filename;
	}
	//else
	return filename.substr(0,idx);
}

int getMenuSelection ()
{
	int selection=0;
	while (true)
	{
		cout << "Choose action do you want to do (type the number)?" << endl;
		cout << "1: Zip a file" <<endl;
		cout << "2: Unzip a file"<<endl;
		cout << "3: Quit the application"<<endl;
		
		cin>>selection;
		if (selection>=1 && selection<=3) break;
		//else
		cout << "Wrong input, choose among options 1, 2 and 3"<<endl<<endl;
	}
	return selection;
}


void zipFile (string inputFile, string outputFile)
{
	cout << "ZIP " << inputFile <<" -> " << outputFile <<endl;
}

void unzipFile (string inputFile, string outputFile)
{
	cout << "UNZIP " << inputFile <<" -> " << outputFile <<endl;
}
