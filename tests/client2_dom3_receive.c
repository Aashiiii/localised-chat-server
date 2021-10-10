#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main()
{
int filee = open("/home/tests/actual_multiple_domain_say", O_WRONLY);
int fd = open("/home/INFO1113/Henry_RD", O_RDONLY);
char buffer[2048]; 
if (filee == -1) {
perror("CANT ACTUAL FILE\n");
} else if (fd == -1) {
perror("CANT OPEN RECEIVE\n");
} else {
	while ( 1 > 0) {
		if ( (read (fd, buffer, 2048)) > 0) {
			printf("received %s \n", buffer);
			write (filee, buffer, 2048);
			exit (0);
		}
	}
}
close(fd);
close(filee);
}
