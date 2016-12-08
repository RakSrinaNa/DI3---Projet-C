#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "instance.h"

int main(int argc, char * argv[])
{
    if(argc >= 3)
    {
        char * filename = argv[0];
    	//int codeType = atoi(argv[1]);
    	//int codeMethod = atoi(argv[2]);
        readFile(filename);
    }
	else
    {
        readFile("MKP-Instances/_mknapcb1_res.txt");
    }
	return 0;
}
