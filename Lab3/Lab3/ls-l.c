#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

void readable(unsigned long);

int main(int argc, char *argv[])	
{
	struct dirent **namelist;
	int n;
	char *fullpath;
	struct stat buf;
	char time[25];
	int i = 0;
	
	if(argc != 2) {
		write(1, "Usage: ./ls-l path\n", 19);
		exit(EXIT_FAILURE);
	}
	n = scandir(argv[1], &namelist, 0, alphasort);
	if (n < 0)
		perror("scandir");
	else {
		while (n >  i) {
			if(strcmp(namelist[i]->d_name, ".") && strcmp(namelist[i]->d_name, "..")) {
				fullpath = malloc(strlen(argv[1]) + strlen(namelist[i]->d_name) + 2);
				sprintf(fullpath, "%s/%s", argv[1], namelist[i]->d_name);
				if(stat(fullpath, &buf) == -1) {
					perror("Stat");
					exit(EXIT_FAILURE);
				}

				switch(buf.st_mode & S_IFMT) { //File type
					case S_IFSOCK: write(1, "s", 1); break;
					case S_IFLNK: write(1, "l", 1); break;
					case S_IFREG: write(1, "-", 1); break;
					case S_IFBLK: write(1, "b", 1); break;
					case S_IFDIR: write(1, "d", 1); break;
					case S_IFCHR: write(1, "c", 1); break;
					case S_IFIFO: write(1, "p", 1); break;
					default: write(1, "?", 1); break;
				}
			
				readable((unsigned long)(buf.st_mode & S_IRWXU)/64); //Owner permissions
				readable((unsigned long)(buf.st_mode & S_IRWXG)/8); //Group permissions
				readable((unsigned long)buf.st_mode & S_IRWXO); // Others permissions
			
				printf(" %d", buf.st_nlink); //Print hard links
			
				printf(" %s", (char *)cuserid(&buf.st_uid));
				printf(" %s", (char *)cuserid(&buf.st_gid));
				printf(" %lld", (long long) buf.st_size);
				//printf(" %s", ctime(&buf.st_mtime));

				strftime(time, 25, "%Y-%m-%d %H:%M", localtime(&buf.st_mtime));
				printf("\t%s", time);
			
				printf(" %s\n", namelist[i]->d_name);
				free(namelist[i]);
			}
			i++;
		}
		free(namelist);
	}
}

void readable(unsigned long m) {
	switch(m) {
		case 7: write(1, "rwx", 3); break;
		case 6: write(1, "rw-", 3); break;
		case 5: write(1, "r-x", 3); break;
		case 4: write(1, "r--", 3); break;
		case 3: write(1, "-wx", 3); break;
		case 2: write(1, "-w-", 3); break;
		case 1: write(1, "--x", 3); break;
		case 0: write(1, "---", 3); break;
	}
}
