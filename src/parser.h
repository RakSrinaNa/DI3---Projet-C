#ifndef PARSER
#define PARSER

#include "stdio.h"
#include "instance.h"

typedef struct
{
	char * filename;
	fpos_t offset;
	int instanceCount;
	int instanceRead;
} Parser;

/**
 * Create a parser structure to read instances one by one.
 *
 * @param filename The path of the file associated to the parser.
 * @return A Parser on the heap.
 */
Parser * parser_create(char * filename);

/**
 * Destroys a Parser previously created with parser_create.
 *
 * @param parser A pointer to the parser to destroy.
 */
void parser_destroy(Parser * parser);

/**
 * Read the next instance inside a Parser.
 *
 * @param parser A pointer to the pointer to read from.
 * @return A pointer to the read instance. NULL if no more to read.
 */
Instance * parser_getNextInstance(Parser * parser);

/**
 * Read a non empty line from a file.
 *
 * @param file The file to read from.
 * @return A string on the heap being the next non empty line in the file. If it couldn't read any, NULL is returned.
 */
char * parser_readLine(FILE * file);

/**
 * Read instance from a file.
 *
 * @param fileName The path to the file to open.
 * @return An array on the heap of the instances.
 */
Instance * parser_readAllFile(char * fileName);

/**
 * Read an instance from the file.
 *
 * @param file The file to read from
 * @param instance A pointer to the instance to write into.
 */
void parser_readInstance(FILE * file, Instance * instance);

/**
 * Transform a line of numbers into an array of integers.
 *
 * @param line The line to parse.
 * @param valuesNumber The maximum number values to read.
 * @return An array of integer on the heap. If there was less values than valuesNumber, the remaining ones are 0.
 */
int * parser_lineToIntArray(char * line, int valuesNumber);

/**
 * Read a line from the file.
 *
 * @param linePtr A pointer to the string that will be read.
 * @param file The file to read from.
 * @return The length read.
 */
int getLine(char ** linePtr, size_t * lineSize, FILE * file);

#endif
