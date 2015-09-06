/* ==================================================================
 * File:  /huffman/main.cpp
 *
 * Brief: Huffman code algorithm
 * Desc:  Zip & Unzip test program
 *
 * Author: Andrew Heebum Kwak (kh-1143@hanmail.net)
 * Date:   2013-06-06
 * ==================================================================
 */

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

void clearScreen();
int getMenuSelection ();
string getFileExtension(string filename);
string getFileWithoutExtension(string filename);
void zipFile (string inputFile, string outputFile);
void unzipFile (string inputFile, string outputFile);


int main(int argc, char const *argv[])
{
	clearScreen();

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
				zipFile (inputFile, inputFile + ".zip");
				break;
			}
			else if (getFileExtension(inputFile) == "zip") // unzip
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

void FreePointer(List* list, Tree* tree)
{
	if(list)
		destroyList(list);
	if(tree)
		destroyTree(tree);
}

void zipFile (string inputFile, string outputFile)
{
	List* list = NULL;
	Tree* tree = NULL;
	char str[BUF_SIZE] = {0,};
	char code[BUF_SIZE*CODE_BUF] = {0,};
	char bit[BUF_SIZE] = {0,};
	int bit_len=0;
	char *treeStr = NULL;

	// File read
	if (!readFile ((char*)inputFile.c_str(), str))
		return;
	
	// Zip text file Using Huffman code
	list = createList();
	tree = createTree();
	
	MakeTable (list, str);			 					// Make Frequency Table
	
	MakeHuffmanTree (tree, list);	 					// Make Huffman Tree

	EncodingFile (tree, str, code);						// Convert string to code
	bit_len = EncodingBit (code, bit);		 			// Convert code to bit

	treeStr = TreeConvertToParenthesisNotation (tree);  // represent tree to parenthesis notation

	cout << "ZIP " << inputFile <<" -> " << outputFile <<endl;
	inputFile += ".zip";

	writeZip ((char*)inputFile.c_str(), treeStr, bit, bit_len);
	
	FreePointer(list, tree);		// Free memory assignment
}

void unzipFile (string inputFile, string outputFile)
{
	List* list = NULL;
	Tree* tree = NULL;
	char str[BUF_SIZE] = {0,};
	char bit[BUF_SIZE] = {0,};
	int bit_len=0;
	char code[BUF_SIZE*CODE_BUF] = {0,};
	char *treeStr = NULL;
	
	// File read
	if (!(treeStr = readZip ((char*)inputFile.c_str(), bit, &bit_len)))
		return;
	
	tree = createTree();
	
	ParenthesisNotationConvertToTree (tree, treeStr);	// Make tree using tree parenthesis notation

	DecodingBit (bit, bit_len, code);					// Convert bit to code
	DecodingFile (tree, code, str);	// Convert code to string
	
	cout << "UNZIP " << inputFile <<" -> " << outputFile <<endl;
	writeFile ((char*)getFileWithoutExtension(inputFile).c_str(), str);
	
	FreePointer(list, tree);		// Free memory assignment
}
