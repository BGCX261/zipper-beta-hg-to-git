
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
\tzipper -c usr/docs/myFile.txt usr/docs/myFolder/ usr/compress/\n\n\
\tIf i want to compress a single file with a\n\
\tspecific compression algorithm\n\
\tI should do the following:\n\
\tzipper -c usr/docs/myFile.txt usr/compress/ 8\n\n"

#define TRAVERSE_DESCRIPTION "Traverse (-t): \n\
\tThis option shows a list of files and directories that a zip file contains.\n\
\tHas the following format:\n\
\t\t-t [Zip path] [Level]\n\
\tWhere:\n\
\t\t[Zip path] Zip file that will be analized.\n\
\t\t[Level] This argument is optional.\n\
\t\t        Indicate until what level will show the zip file hierachy.\n\
\t\t        The level must be greater than 0.\n"

#define TRAVERSE_EXAMPLE "\n\tExample:\n\
\tIn order to use the traverse(-t) option, \n\
\tLook the following example:\n\
\tIf you want to navigate the following zip file:\n\
\t\texample.zip\n\
\tIn this location: \n\
\t\t/usr/docs\n\
\tDo the following:\n\
\t\tzipper -t /usr/docs/example.zip\n\n"

#define DECOMPRESSION_DESCRIPTION "Decompress (-d):\n\
\tThis option decompress a zip file.\n\
\tHas the following format:\n\
\t\t-d [Zip path] [Destiny path]\n\
\tWhere:\n\
\t\t[Zip path] Zip file that will be decompressed\n\n\
\t\t[Destiny path] The location where the content of the \n\
\t\tzip file will be stored\n"

#define DECOMPRESSION_EXAMPLE "\n\tExample:\n\
\tIn order to use the decompression(-d) option, \n\
\tyou can look the following example:\n\
\tIf you want decompress the following file:\n \
\t\t/usr/example.zip\n\
\tIn this location:\n\
\t\t/usr/Docs/folder\n\
\tDo the following:\n\
\t\tzipper -d /usr/usr/example.zip /usr/Docs/folder\n\n"

#define HELP_DESCRIPTION "Help(-h):\n\
\tDisplay the help text of all options\n"

#define HELP_TEXT APLICATION_DESCRIPTION COMPRESSION_DESCRIPTION COMPRESSION_EXAMPLE \
TRAVERSE_DESCRIPTION TRAVERSE_EXAMPLE DECOMPRESSION_DESCRIPTION DECOMPRESSION_EXAMPLE HELP_DESCRIPTION
#endif	/* HELP_H */

