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
int fd = open("/home/COMP2017/Aash_WR", O_WRONLY);
char message[2048]; 
message[0] = 2;
message[1] = 0;
message[2] = 'h';
message[3] = 'o';
message[4] = 'w';
message[5] = 'z';
message[6] = 'z';
int i = 0;
for (i = 7; i < 2048; i++) {
	message[i] = '\0';
}
message[2047] = 255;
write(fd, message, 2048);
close(fd);
}
