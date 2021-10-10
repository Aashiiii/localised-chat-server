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
message[2] = 'A';
message[3] = 'a';
message[4] = 's';
message[5] = 'h';
int i = 0;
for (i = 6; i < 258; i++) {
	message[i] = '\0';
}
message[258] = 'C';
message[259] = 'O';
message[260] = 'M';
message[261] = 'P';
message[262] = '2';
message[263] = '0';
message[264] = '1';
message[265] = '7';
for (i = 266; i < 2048; i++) {
	message[i] = '\0';
}
write (fd, message, 2048);
close (fd);
}
