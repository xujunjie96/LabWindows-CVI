#include <cvirte.h>
#include <dllres.h>  
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;    /* out of memory */
	InitUIForDLL();//µ÷ÓÃdllº¯Êý
	return 0;
}
