/**
 *  * @file     xsh_echo.c
 *   * @provides xsh_echo
 *    *
 *     * $Id$
 *      */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */
 
#include <stdio.h>
#include <kernel.h>
#include <shell.h>
#include <stdlib.h>
#include <string.h> 
/**
 *  * Shell command echos input text to standard out.
 *   * @param stdin descriptor of input device
 *    * @param stdout descriptor of output device
 *     * @param stderr descriptor of error device
 *      * @param args array of arguments
 *       * @return OK for success, SYSERR for syntax error
 *        */
command xsh_palindrome(ushort stdout, ushort stdin, ushort stderr, ushort nargs, char *args[])
{
    int i,j,check=0;  /* counter for looping through arguments */
 
    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
    {
        fprintf(stdout, "Usage: clear\n");
        fprintf(stdout, "Clears the terminal.\n");
        fprintf(stdout, "\t--help\t display this help and exit\n");
        return SYSERR;
    }
 
    /* taking the string */
	char *string = args[1];
	//frpintf(stdout, "%s\n",string); 
	int len = strlen(string);
	//fprintf(stdout, "%d",len);
	j = len-1;
	/*checking whether it is palindrome by moving one character from first and last*/
    	for ( i = 0; i < len/2; i++,j-- ){
		if(string[i]!=string[j])check=1;
	}
	if(check==1)
    	{
        	fprintf(stdout, "%s ", "no");
    	}	
	else{
		fprintf(stdout,"%s","yes");
	}
 
    /* Just so the next prompt doesn't run on to this line */
    fprintf(stdout, "\n");
 
    /* there were no errors so, return OK */
    return OK;
}
