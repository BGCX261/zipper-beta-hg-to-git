
#ifndef OUTPUTERROR_H
#define	OUTPUTERROR_H

#include "help.h"

/**
 *Here is defined the output error for user
 */

#define OPTION_ERROR "Zipper:unknown option\n"

#define ARGS_ERROR "Zipper:Input arguments error\n"

#define FILE_NOT_FOUND_ERROR "Zipper:File not Found\n"

#define COMPRESSION_NOT_SUPPORTED_ERROR "Zipper: Compression Method Not Supported\n"

#define CORRUPT_FILE_ERROR "Zipper:Current File is Corrupted\n"

#define INVALID_ZIP_FILE_ERROR "Zipper: Invalid zip file\n"

#define OK_PROCESS "Zipper: Process Success\n"

#define CAN_NOT_OPEN_ERROR "Zipper: Can not open the file\n"

#define CAN_NOT_FIND_TARGET_ERROR "Zipper: Can not find the target path\nNote:Check if that directory exists\n"

#define UNKNOW_OPTION OPTION_ERROR HELP_TEXT

#define UNKNOW_ARGS ARGS_ERROR HELP_TEXT

#define UNKNOW_COMPRESSION_ARGS ARGS_ERROR COMPRESSION_DESCRIPTION

#define UNKNOWN_TRAVERSE_ARGS ARGS_ERROR TRAVERSE_DESCRIPTION

#endif	/* OUTPUTERROR_H */

