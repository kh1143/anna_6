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
	verifyId (STUDENT_ID);
	clearScreen();

	while (true)
	{
		int selection= getMenuSelection();

		if (selection==3) break; // quit the program

		while (true)
		{				
			List* list = NULL;
			Tree* tree = NULL;
			char str[BUF_SIZE] = {0,};
			char code[BUF_SIZE*CODE_BUF] = {0,};
			char bit[BUF_SIZE] = {0,};
			int table_size=0;
			int bit_len=0;
			CodeTable *codetable = NULL;
			char *treeStr = NULL;
			
			cout << "Type the name of the file that you want to use" <<endl;
			string inputFile;
			cin >> inputFile;

			if (selection==1) // zip
			{
				// File read
				if (!readFile ((char*)inputFile.c_str(), str))
					break;

				// Zip text file Using Huffman code
				list = createList();
				tree = createTree();
				MakeTable (list, str);			 // Make Frequency Table
				table_size = getListSize (list);		 // Get Size
				codetable = new CodeTable[table_size]; // dynamic array
				MakeHuffmanTree (tree, list);	 // Make Huffman Tree
				HuffmanEncode (tree, codetable); // Make Codetable
				EncodingFile (codetable, table_size, str, code);	// Convert string to code
				bit_len = EncodingBit (code, bit);		 // Convert code to bit
				treeStr = TreeConvertToParenthesisNotation (tree); // represent tree to parenthesis notation

				/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				displayCode(codetable, size);
				TreeConvertToParenthesisNotation (tree, treeStr);
				cout << treeStr<<endl;
				Tree* decodeTree = createTree();
				ParenthesisNotationConvertToTree (decodeTree, treeStr);
				CodeTable *test = new CodeTable[size];
				HuffmanEncode (decodeTree, test);
				displayCode(test, size);									
				///////*//////////////////////////////////////////////////////////////////////////////////////////////////////


				// File save
				zipFile (inputFile, inputFile + ".zip");
				inputFile += ".zip";
				writeZip ((char*)inputFile.c_str(), treeStr, table_size, bit, bit_len);

				break;
			}
			else if (getFileExtension(inputFile) == "zip") // unzip
			{
				// File read
				if (!(treeStr = readZip ((char*)inputFile.c_str(),
											&table_size, bit, &bit_len)))
					break;
				tree = createTree();
				ParenthesisNotationConvertToTree (tree, treeStr);
				codetable = new CodeTable[table_size];
				HuffmanEncode (tree, codetable);

				DecodingBit (bit, bit_len, code);					// Convert bit to code
				DecodingFile (codetable, table_size, code, str);	// Convert code to string

				unzipFile (inputFile, getFileWithoutExtension(inputFile));
				writeFile ((char*)getFileWithoutExtension(inputFile).c_str(), str);
				break;

			}
			else
			cout <<"Invalid input file"<<endl;

			// Free assigned memory
			for(int i=0; i<table_size; i++)
				if (codetable[i].code)
					delete []codetable[i].code;
			if (codetable)
				delete []codetable;
			if(list)
				destroyList(list);
			if(tree)
				destroyTree(tree);
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
