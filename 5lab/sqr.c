#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int k=atoi(argv[argc-1]);
	char *argss[argc];
	char *result;
	char ch[10];
	char init[]="./";
	if(argc>1)
	{

		k=k*k;
		if(argc>=3)
		{
			for(int i=0;i<argc-1;i++)
			{

				argss[i]=argv[i+1];
			}
				sprintf(ch, "%d",k);
				printf("Pid is %d \n",getpid());
				argss[argc-2]=ch;
				argss[argc-1]=NULL;
				argss[0]=strcat(init,argss[0]);
				execvp(argss[0],argss);




		}
	
	else
	{
		printf("%d",k);
	}
}
	else
	{

		printf("Error");
	}
	
	
}