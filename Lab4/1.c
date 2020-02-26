/*----------------------------------------------------*/
/* Code to read a n chars from t'th postion in a file */
/*        Auther VR<vrnithinkumar@gmail.com>          */
/*----------------------------------------------------*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
 
int main(int argc,char* argv[])
{
        int file;
        int n=atoi(argv[2]),t=atoi(argv[1]);            //Changing the char array to integer using stlib function
        char buffer[n];                                 //Setting buffer size [n]

        
        if((file=open(argv[3],O_RDONLY)) < -1){
        	printf("Error on file opening");
        	return 1;
        }
                
		
        if(lseek(file,t,SEEK_SET) < 0){    			// Setting initial position of to t for read
        	printf("Error on file Seeking");
        	return 1;
        }

        if(read(file,buffer,n) != n)  				//reading
        {
        	printf("Error on file opening");
        	return 1;
        }
        printf("%s\n",buffer);						//printing the buffer
 
        return 0;
}