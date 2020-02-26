#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
	pid_t child;
	if((child=fork())==0){
		printf("Cool its child %d \n",child);
		exit(0);

	}
	printf("Its the parent %d\n",child);


}