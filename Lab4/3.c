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

void Dir_Walk(char *DirName)                        								//Function To be called recursivly  
{

	char *Temp;
	struct stat finfo;
	struct dirent *Dir_Struc;
	DIR* fk=opendir(DirName);
	chdir(DirName);                                   //Going to next Dir
		while((Dir_Struc=readdir(fk)))
		{
			
			stat(Dir_Struc->d_name,&finfo);
			Temp=(Dir_Struc->d_name);
			if(((*(Temp)=='.') && (*(Temp+1)=='\0' ))||((*(Temp)=='.') && (*(Temp+1)=='.' ) && (*(Temp+2)=='\0')))  //To Avoid .. & .
			continue;                                                                                               
		
			else{
				if(S_ISDIR(finfo.st_mode))
				{
					Dir_Walk(Dir_Struc->d_name);     //Calling Dir_Walk again for recursive dir walk
					printf("%s\n",Dir_Struc->d_name);
				}
				else
				{
					printf("%s\n",Dir_Struc->d_name);
				}
			}
		}
		chdir("..");    // Going Back to dir
		closedir(fk);
	
	
}	
	

main(int argc,char* argv[])
{
	struct stat info;
	int fd;
	if(stat(argv[1],&info)<0)
		return 1;
	if(S_ISDIR(info.st_mode)){
	Dir_Walk(argv[1]);
	
	}
	else{
		 printf("Given a file\n");
	}
	 
	return 0;
}
