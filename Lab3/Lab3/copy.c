#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd1, fd2;
	ssize_t nread, nwritten;
	char buf[4096], *out_ptr;
	
	if ( argc != 3) {
		printf("Incorrect arguments\nUsage: ./cp source destination\n");
	}
	fd1 = open(argv[1], O_RDONLY);
	
	if (fd1 == -1) {
		perror("Opening failed");
		exit(EXIT_FAILURE);
	}
	
	fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666);
	
	if (fd2 == -1) {
		perror("Opening failed");
		close(fd1);
		exit(EXIT_FAILURE);
	}
	
	while ((nread = read(fd1, buf, sizeof(buf))) && nread > 0) {
		out_ptr = buf;
		do {
			nwritten = write(fd2, out_ptr, nread);
			if(nwritten > 0) {
				nread -= nwritten;
				out_ptr += nwritten;
			}
			else {
				perror("Write error");
				exit(EXIT_FAILURE);
			}
		} while(nread > 0);
	}
	
	if(close(fd2) < 0) {
		perror("Close error");
	}
	close(fd1);
	
	return 0;
}
