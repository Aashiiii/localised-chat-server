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
int filee = open("/home/tests/actual_same_domain_receive", O_WRONLY);
int fd = open("/home/COMP2017/Alice_RD", O_RDONLY);
char buffer[2048]; 
	while ( 1 > 0) {
		if ( (read (fd, buffer, 2048)) > 0) {
			write (filee, buffer, 2048);
			break;
		}
	}
close(fd);
close(filee);
}
