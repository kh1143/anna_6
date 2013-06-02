#ifndef _FILE_H_
#define _FILE_H_

#include "types.h"

bool readFile (char* filename, char *str);
char* readZip (char* filename, char *bit, int *bit_len);

bool writeFile(char* filename, char* str);
bool writeZip(char* filename, char *treeStr, char* bit, int bit_len);

#endif
