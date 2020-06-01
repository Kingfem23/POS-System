/**
 Author: Matthew Ajayi
 Date: June 19th, 2017
 Purpose: Initializing the test functions
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
**/

#include <stdio.h>
#include <stdlib.h>

/** Uses the integers to test if what ever entered passes or fails the test. 
*@pre Value must be valid.
*@param a constant integer that depends if you pass or fail test.
**/
int printPassFail( const int result );

/** Increments integers to see what test number you are at and prints an intro showing what the test will test for. 
*@pre Values must be valid.
*@param a constant integer that increments and a statement for the test performed.
**/
void printTestIntroInfo( int testNumber, const char *intro);
