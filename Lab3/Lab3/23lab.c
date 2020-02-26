#include <stdio.h>
#include<fcntl.h>

int main(int argc,char* argv[]){

	int fd1, fd2;
	char buf[4096];
	int data;
	if(argc!=3){
		write(1, "Error Incorrect arguments",25);
	}
	fd1=open(argv[2],O_WRONLY|O_CREAT);
	fd2=open(argv[1],O_RDONLY);
	
	data=read(fd2,buf,sizeof(buf));
		printf("%d",data);
		
		
	
	//close(fd1);
	close(fd2);



}

