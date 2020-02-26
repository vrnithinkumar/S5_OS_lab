#include <sys/utsname.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

struct utsname buf;

int main() {
	if(uname(&buf) == 0) {
		write(1, "OS Name: ", 9);
		write(1, buf.sysname, strlen(buf.sysname));
		write(1, "\n", 1);
		write(1, "Network Name: ", 14);
		write(1, buf.nodename, strlen(buf.nodename));
		write(1, "\n", 1);
		write(1, "OS Release: ", 12);
		write(1, buf.release, strlen(buf.release));
		write(1, "\n", 1);
		write(1, "Version: ", 9);
		write(1, buf.version, strlen(buf.version));
		write(1, "\n", 1);
		write(1, "Hardware Identifier: ", 21);
		write(1, buf.machine, strlen(buf.machine));
		write(1, "\n", 1);
	}
	else
		perror("Uname");
}
