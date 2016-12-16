#ifndef PARSER
#define PARSER

#include "stdio.h"
#include "instance.h"

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
Instance * parser_readFile(char * fileName);

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
