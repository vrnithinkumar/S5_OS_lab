/*----------------------------------------------------------*/
/* Code Purpose:Print size of all files and folders of a    */
/*              given directory                             */
/*          Auther: VR<vrnithinkumar@gmail.com>             */
/*----------------------------------------------------------*/


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

long fsize(char *fname)                        								//Function To be called recursivly  
{
	long sum=0,tempsize=0;
	char *Temp;
	struct stat info;
	struct dirent *dptr;
	DIR* fk=opendir(fname);
	chdir(fname);
		while((dptr=readdir(fk))!=NULL)
		{
			
			stat(dptr->d_name,&info);
			Temp=(dptr->d_name);
			if(((*(Temp)=='.') && (*(Temp+1)=='\0' ))||((*(Temp)=='.') && (*(Temp+1)=='.' ) && (*(Temp+2)=='\0')))  //To Avoid .. & .
			continue;                                                                                               
		
			else{
				if(S_ISDIR(info.st_mode))
				{
					tempsize=fsize(dptr->d_name);
					sum+=tempsize;
					printf("%s -- %d bytes\n",dptr->d_name,tempsize);
				}
				else
				{
					sum+=info.st_size;
					printf("%s -- %d bytes \n",dptr->d_name,info.st_size);
				}
			}
		}
		chdir("..");
		closedir(fk);
	return sum;
	
}	
	

main(int argc,char* argv[])
{
	struct stat info;
	int fd;
	if(stat(argv[1],&info)<0)
		return 1;
	if(S_ISDIR(info.st_mode)){
	printf("%s size is %d bytes\n",argv[1],fsize(argv[1]));
	
	}
	else{
		 printf("Size of the File is -- %d bytes\n",info.st_size);
	}
	 
	return 0;}
