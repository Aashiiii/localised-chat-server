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
int fd = open("/home/gevent", O_WRONLY);
char message[2048]; 
message[0] = 0;
message[1] = 0;
message[2] = 'L';
message[3] = 'e';
message[4] = 'x';
message[5] = 'i';
int i = 0;
for (i = 6; i < 258; i++) {
	message[i] = '\0';
}
message[258] = 'I';
message[259] = 'N';
message[260] = 'F';
message[261] = 'O';
message[262] = '1';
message[263] = '1';
message[264] = '1';
message[265] = '3';
for (i = 266; i < 2048; i++) {
	message[i] = '\0';
}
write (fd, message, 2048);
close (fd);
}
