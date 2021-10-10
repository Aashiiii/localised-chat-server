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
int fd = open("/home/INFO1113/Lexi_WR", O_WRONLY);
if (fd == -1) {
}
char message[2048]; 
message[0] = 1;
message[1] = 0;
message[2] = 'j';
message[3] = 'o';
message[4] = 'i';
message[5] = 'n';
message[6] = 'e';
message[7] = 'd';
int i = 0;
for (i = 8; i < 2048; i++) {
	message[i] = '\0';
}
message[2047] = 255;
write(fd, message, 2048);
close(fd);
}
