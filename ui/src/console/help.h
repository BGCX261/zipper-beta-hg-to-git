
#ifndef HELP_H
#define	HELP_H

/**
 *Here is defined the help for user
 */

#define APLICATION_DESCRIPTION "Zipper Help:\n"

#define COMPRESSION_DESCRIPTION "Compress(-c): \n\
\tThat option compress a list of file and directories\n\
\tand has the following format.\n\n\
\t-c [Source Paths...] [Destiny Path] [Compression Method]\n\
\tWhere:\n\
\t[Source Paths...] The Files and Directories to will be compressed\n\
\t[Destiny Path] The location where the zip file will be stored\n\
\t[Compression Method]This argument is optional and represents the\n\
\t\tapplied compression algorithm introduced\n\
\t\tthe argument is a number that represents that\n\
\t\tcompression algorithm will be used\n\
\t\tAlgorithms are:\n\
\t\t0-Non Compression Algorithm\n\
\t\t8-Deflate\n"

#define COMPRESSION_EXAMPLE "\tExample:\n\n\
\tIn order to use the compression(-c) option, \n\
\tyou can look the following example:\n\
\tIf i want to compress the following files:\n\
\tusr/docs/myFile.txt\n\
\tusr/docs/myFolder\n\
\tIn this location: usr/compress\n\
\tI should do the following:\n\
\tzipper -c usr/docs/myFile.txt usr/docs/myFolder usr/compress\n\n\
\tIf i want to compress a single file with a\n\
\tspecific compression algorithm\n\
\tI should do the following:\n\
\tzipper -c usr/docs/myFile.txt usr/compress 8\n\n"

#define HELP_DESCRIPTION "Help(-h):\n\
\tDisplay the help text of all options\n"

#define HELP_TEXT APLICATION_DESCRIPTION COMPRESSION_DESCRIPTION COMPRESSION_EXAMPLE HELP_DESCRIPTION
#endif	/* HELP_H */

