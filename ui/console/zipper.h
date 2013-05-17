
#ifndef ZIPPER_H
#define	ZIPPER_H

#include "errorcode.h"
#include "zipperlib.h"

#define DEFAULT_ARGS 2

#define COMPRESSION_ARGS 4

#define BEGIN_INDEX_SOURCE_ARGS 2

#define CONSOLE_OPTION_LENGTH 2

#define AMOUNT_COMPRESSION_ALGORITHMS 10

class ConsoleZipper{

public:
    static char* runCommand(int argc,char** argv);
private:
    static char* executeOption(char option,int argc, char** argv);
    static char* compressOption(int argc,char** argv);
    static char* helpOption();
    static char* errorCodeToString(ErrorCode errorCode);
    static char** getSourceCompressionArgs(char** argv, int end);
    
    
};


#endif	/* ZIPPER_H */

