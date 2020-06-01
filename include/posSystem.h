/*
 Author: Matthew Ajayi
 Date: August 6th 2017
 Purpose: test program.
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
*/

#include "balancedTreeAPI.h"

typedef struct data
{
  char * iD;
  char * productName;
  char * pub;
  char * genre;
  int tax;
  double price;
  int quantity; 

} Data;

/**Function to parse the tree
 *@param file is the file to be parsed and inserted into the tree
 *@param myTree is the tree that was previously intialized
 *@return void
 **/
void parseFile(FILE * file, Tree * myTree);

/**Function to convert string to integer manually
 *@param name is the name to be converted
 *@param length is the length of the name
 *@return integer
 **/
int convertToInt(char * name, int length);

/**Function to manually parse a file
 *@param str is the name to be parsed
 *@param delim is delimeter we are parsing by
 *@return char pointer
 **/
char *zstring_strtok(char *str, const char *delim);
