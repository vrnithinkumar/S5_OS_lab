#include<fcntl.h>
#include<stdio.h>

int main(int argc , char *argv[])
{
	int fds1,fds2,a;
	char ch;
	if (argc !=3 )
		{
			printf("exactly 2 arguments expected");
			return 0;
		}
	else
		{
			fds1=open(argv[1],O_RDONLY);
			fds2=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC);
			a=read(fds1,&ch,1);
			while(a!=0 && a!=-1)
			{
				printf("%c",ch);

				a=write(fds2,&ch,1);
				if(a==-1) continue;
				a=read(fds1,&ch,1);
			}
		}
			
}
