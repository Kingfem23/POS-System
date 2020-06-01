/*
 Author: Matthew Ajayi
 Date: August 6th 2017
 Purpose: test program.
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
*/

#include "posSystem.h"

//parse the file that is inputted
void parseFile(FILE * file, Tree * mList)
{
    char line[256];

    while(fgets(line,sizeof(line), file) != NULL)
    { 
        Data * m = (Data *) malloc(sizeof(Data));
        char * productName = malloc(sizeof(char*));
        char * productID = malloc(sizeof(char*));
        char * pub = malloc(sizeof(char*));
        char * genre = malloc(sizeof(char*));
        char * taxable =malloc(sizeof(char*));
        char * price = malloc(sizeof(char*));
        char * p = malloc(sizeof(char*));
        char * quantity = malloc(sizeof(char*));

        productID = zstring_strtok(line, ",");
        productName = zstring_strtok(NULL, ",");
        pub = zstring_strtok(NULL, ",");
        genre = zstring_strtok(NULL, ",");
        taxable = zstring_strtok(NULL, ",");
        price = zstring_strtok(NULL, ",");
        p = strtok(price, ",$\t\r");
        quantity = zstring_strtok(NULL, ",\t\r\n");

        m -> iD = malloc(sizeof(char)* (strlen(productID)) + 1);
        m -> productName = malloc(sizeof(char)* (strlen(productName)) + 1);
        m -> pub = malloc(sizeof(char)* (strlen(pub)) + 1);
        m -> genre = malloc(sizeof(char) * strlen(genre) + 1);
        m -> tax = convertToInt(taxable, strlen(taxable));
        m -> price = atof(p);
        m -> quantity = atoi(quantity);

        strcpy(m -> iD, productID);
        strcpy(m -> productName, productName);
        strcpy(m -> pub, pub);
        strcpy(m -> genre, genre);
      
        // printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d\n", m -> iD, m -> productName, m -> pub, m -> genre, m -> tax);

        treeInsertNode(mList, m);
    }
    
}

//Convert string value to int
int convertToInt(char * name, int length)
{
    int value;
    value = 0;
    for(int i = 0; i < length; i++)
    {
    	char c = name[i];
    	value = value + (c - '0');
    }
	
	return value;
}

//Manually Parse string
char *zstring_strtok(char *str, const char *delim) 
{
    static char *static_str=0;      /* var to store last address */
    int index=0, strlength=0;       /* integers for indexes */
    int found = 0;                  /* check if delim is found */

    /* delimiter cannot be NULL
    * if no more char left, return NULL as well
    */
    if (delim==0 || (str == 0 && static_str == 0))
        return 0;

    if (str == 0)
        str = static_str;

    /* get length of string */
    while(str[strlength])
        strlength++;

    /* find the first occurance of delim */
    for (index=0;index<strlength;index++)
        if (str[index]==delim[0]) {
            found=1;
            break;
        }

    /* if delim is not contained in str, return str */
    if (!found) {
        static_str = 0;
        return str;
    }

    /* check for consecutive delimiters
    *if first char is delim, return delim
    */
    if (str[0]==delim[0]) {
        static_str = (str + 1);
        return (char *)delim;
    }

    /* terminate the string
    * this assignmetn requires char[], so str has to
    * be char[] rather than *char
    */
    str[index] = '\0';

    /* save the rest of the string */
    if ((str + index + 1)!=0)
        static_str = (str + index + 1);
    else
        static_str = 0;

        return str;
}


