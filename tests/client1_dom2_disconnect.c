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
int fd = open("/home/INFO1110/Jay_WR", O_WRONLY);
char message[2048]; 
message[0] = 7;
message[1] = 0;
int i = 0;
for (i = 2; i < 2048; i++) {
	message[i] = '\0';
}
message[2047] = 255;
write(fd, message, 2048);
close(fd);
}
