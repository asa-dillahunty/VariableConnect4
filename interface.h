#ifndef __interface_INCLUDED__
#define __interface_INCLUDED__

#include <stdbool.h>

extern int getNum(char* response, int min, int max);
extern bool yesNo(char* response);
extern void printFile(char* filename);
extern void printMenu();
extern void startInterface();

#endif
