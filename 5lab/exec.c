#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	 char *args[4];
   args[0] = argv[1];
   args[1] = argv[2];
   args[2] = argv[3];
   args[3] = NULL;
	execvp(argv[1],args);
}