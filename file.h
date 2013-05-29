#ifndef _FILE_H_
#define _FILE_H_

#include "types.h"

bool readFile (char* filename, char *str);
CodeTable* readZip (char* filename, int *size, char *str);

bool writeFile(char* filename, char* str);
bool writeZip(char* filename, CodeTable *ct, int size, char* str);


#endif
