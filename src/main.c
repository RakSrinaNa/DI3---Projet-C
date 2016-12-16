#include <string.h>

#include "mainUnit.h"
#include "parser.h"

int main(int argc, char * argv[])
{
	if(argc >= 4)
	{
		char * filename = argv[1];
		//int codeType = atoi(argv[2]);
		//int codeMethod = atoi(argv[3]);
		parser_readFile(filename);
	}
	else if(argc == 2) // Used to start tests
	{
		if(strcmp(argv[1], "test") == 0)
		{
			mainUnit();
		}
		else if(strcmp(argv[1], "ker") == 0)
        {
            mainKergosien();
        }
	}
	else
	{
		parser_readFile("MKP-Instances/_mknapcb1_res.txt");
	}
	return 0;
}
