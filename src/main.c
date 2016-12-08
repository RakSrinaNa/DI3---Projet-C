#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainUnit.h"
#include "parser.h"
#include "instance.h"

int main(int argc, char * argv[])
{
    if(argc >= 4)
    {
        char * filename = argv[1];
    	//int codeType = atoi(argv[2]);
    	//int codeMethod = atoi(argv[3]);
        readFile(filename);
    }
    else if(argc == 2)
    {
        if(strcmp(argv[1], "test") == 0)
        {
            mainUnit();
        }
    }
	else
    {
        readFile("MKP-Instances/_mknapcb1_res.txt");
    }
	return 0;
}
