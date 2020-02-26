#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char* newenv[2];
	char* argss[2];
	newenv[0]="PATH=/home/vr/Desktop/S5/OS_lab/5lab";
	newenv[1]=NULL;
	argss[0]="just";
	argss[1]=NULL;
	execvp("just",argss);
}