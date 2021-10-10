#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L
#include "server.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <poll.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>


struct pollfd fds[3];
int pong = 1;   //Flag to check if the client replied with PONG or not.
int disc = 1;   //Flag to indicate when disconnect message is received.
uint64_t max = MAX;
/*
This function is used to send a message to all the other clients.
Client handler uses this function for both RECEIVE and RECVCONT.

parameter:
readpipe: path of the clients readpipe (char*)
writepipe: path of the clients write pipe (char*)
identifier_read: the array of identifier message sent by client (char*)
domain_read: the array of domain message sent by client (char*)
identifier: the identifier name used in filepath (char*)
domain: the domain name used in filepath (char*)
buffer: the message sent by the client (char*)
buf_receive: the message to be sent to other clients (char*)

return:
This function does not returns anything.
It just realys the message to all the other clients.
*/
void receive (char* readpipe, char* writepipe, char* identifier_read, 
                char* domain_read, char* identifier, char* domain, char* buffer, 
              char* buf_receive) {

	DIR *d;
	struct dirent *dir;
	d = opendir (domain);
	if (d == NULL) {
		perror("Could not open directory \n");			
	} else {
		while ((dir = readdir(d)) != NULL) {
			if (strstr (dir->d_name, identifier)) {
                // the client that sent the message.
			} else if (strstr(dir->d_name, "RD")) {
                // readpipe of other clients
				char filename [PATH_LEN];
				sprintf (filename, "%s/%s", domain, dir->d_name);
				int f = open (filename , O_WRONLY | O_NONBLOCK);
				int m = 0;
				while (f == -1) {
					f = open (filename , O_WRONLY | O_NONBLOCK);
					m += 1;
					if (m == MAX) {
						break;
					}
				}
				fds[1].fd = f;
				fds[1].events = POLLOUT;
				poll (fds, 2, -1);
				if(fds[1].revents & POLLOUT) {
					write (f, buf_receive, LENGTH);
				}
				close (f);
			}
		}
		closedir (d);
	}
}

/*
This function is used by client handler to process the SAY and 
SAYCONT message sent by the client.

parameter:
readpipe: path of the clients readpipe (char*)
writepipe: path of the clients write pipe (char*)
identifier_read: the array of identifier message sent by client (char*)
domain_read: the array of domain message sent by client (char*)
identifier: the identifier name used in filepath (char*)
domain: the domain name used in filepath (char*)
buffer: the message sent by the client (char*)
cont: 0 denotes the message is of type SAYCONT,else it is of type SAY (int)

return:
This function does not returns anything.
*/
void say (char* readpipe, char* writepipe, char* identifier_read, 
            char* domain_read, char* identifier, char* domain, char* buffer, 
          int cont) {

	char say_message[MESSAGE];
	char *q;
	q = &buffer[2];
	memcpy(say_message,q ,MESSAGE);
	char buf_receive[LENGTH];
	buf_receive[0] = RECV;
	if (cont == 0) {
        // SAYCONT message
		buf_receive[0] = RECVCONT;
	}
	buf_receive[1] = 0;
	memcpy (&buf_receive[2], identifier_read, IDEN);
	memcpy (&buf_receive[IDEN + 2], say_message, MESSAGE);
	if (cont == 0) {
        // SAYCONT message
		buf_receive[LENGTH - 1] = buffer[LENGTH - 1];
	}
	receive (readpipe, writepipe, identifier_read, domain_read, identifier, domain, 
					buffer, buf_receive);
}

/*
This function disconnects the client from the server.

parameters:
readpipe: path of the clients readpipe (char*)
writepipe: path of the clients write pipe (char*)

return:
It does not returns anything (void).
*/
void disconnect (char* writepipe, char* readpipe) {
	unlink (writepipe);
	unlink (readpipe);
	kill(getppid(), SIGUSR1);
}

/*
This function is used by client handler to wait for its child.
*/
void kill_ping (int sig) {
	wait (NULL);
}

/*
This function is the client handler.

parameter:
readpipe: path of the clients readpipe (char*)
writepipe: path of the clients write pipe (char*)
identifier_read: the array of identifier message sent by client (char*)
domain_read: the array of domain message sent by client (char*)
identifier: the identifier name used in filepath (char*)
domain: the domain name used in filepath (char*)

return:
This function does not returns anything.
*/
void client_handler (char* readpipe, char* writepipe, char* identifier_read, 
						char* domain_read, char* identifier, char* domain) {
	int result = fork ();
	if (result == 0) {
		//child
        //It will handle PING-PONG
		while ( 1 > 0 ) {
			if (disc == 0) {
				sleep (1);
				exit (0);
			}
			sleep (SLEEP_TIME);
			if (pong == 0) {
                //Client did not send back PONG
				int rp = open(writepipe, O_WRONLY | O_NONBLOCK);
				char dis_message[LENGTH];
				dis_message[0] = DISCONNECT;
				dis_message[1] = 0;
				int i = 0;
				for (i = 2; i < LENGTH; i++) {
					dis_message [i] = '\0';
				}
				write (rp, dis_message, LENGTH);
				close (rp);
                // Sending signal to parent (client handler) 
				kill(getppid(), SIGUSR2);
				exit (0);
			}
			char ping_message[LENGTH];
			ping_message[0] = PING;
			ping_message[1] = 0;
			int i = 0;
			for (i = 2; i < LENGTH; i++) {
				ping_message [i] = '\0';
			}
			char filename[PATH_LEN];
			sprintf (filename, "%s/%s_RD", domain, identifier);
			int fd = open (filename , O_WRONLY | O_NONBLOCK);
			write (fd, ping_message, LENGTH);
			close (fd);
            //Reset flag to 0. It will change to 1, if client replies with PONG.
			pong = 0; 
		}
	} else {
		signal (SIGUSR2, &kill_ping);
		char buffer[LENGTH];
		
		while (1 > 0) {
			int rp = open(writepipe, O_RDONLY | O_CREAT);
			if (rp < 0) {
				// Pipe could not be opened
			}
			fds[0].fd = rp;
			fds[0].events = POLLIN;
			poll (fds, 1, -1);
			if (fds[0].revents & POLLIN) {
				if ( (read (rp, buffer, LENGTH)) > 0) {
					close (rp);

					if (buffer[0] == SAY && buffer[1] == 0){
						//SAY
						say (readpipe, writepipe, identifier_read, domain_read, identifier, domain, buffer, 1);
					}
						
					if (buffer[0] == SAYCONT && buffer[1] == 0){
						//SAYCONT
						say (readpipe, writepipe, identifier_read, domain_read, identifier, domain, buffer, 0);
					}
						
					if (buffer[0] == DISCONNECT && buffer[1] == 0){
						//DISCONNECT
						disconnect (writepipe, readpipe);
						sleep (2);
						disc = 0;
						exit (0);
					}
					if (buffer[0] == PONG && buffer[1] == 0){
                        //PONG
						pong = 1;
					}				
				}
			}
		}
	}
}

/*
This function is used by server to wait for its child.
*/
void kill_child (int sig) {
	wait (NULL);
}

/*
GLOBAL PROCESS
*/
int main (int argc, char** argv) {
	signal (SIGUSR1, &kill_child);
	char fifoname [IDEN];
	strcpy (fifoname, "gevent");
	if (mkfifo (fifoname, 0777) == -1) {
		//Couldnt create pipe gevent!!! 
	}

	while (1 > 0) {
		int gevent = open(fifoname, O_RDONLY);
		int i = 0;
		char buf[LENGTH];
		if ( (read (gevent, buf, sizeof (buf))) > 0) {
			if (buf[1] == 0 && buf[0] == 0){
				char identifier_read[IDEN];
				char domain_read[IDEN];
				char *p;
				p = &buf[2];
				memcpy(identifier_read, p ,IDEN);
				p = &buf[IDEN + 2];
				memcpy(domain_read, p ,IDEN);
				char identifier[IDEN];
				char domain[IDEN];
				
                // Finding the identifier name 
				i = 0;
				int ic = 0;
				while (identifier_read[i] == '\0' && i < IDEN) {
					i += 1;
				}
				while (identifier_read[i] != '\0' && i < IDEN) {
					identifier[ic] = identifier_read[i];
					ic += 1;
					i += 1;
				}
				identifier[i] = '\0';
				
                // Finding the domain name 
				i = 0;
				int dc = 0;
				while (domain_read[i] == '\0' && i < IDEN ) {
					i += 1;
				}
				while (domain_read[i] != '\0' && i < IDEN ) {
					domain[dc] = domain_read[i];
					dc += 1;
					i += 1;
				}
				domain[i] = '\0';

				struct stat st = {0};
				if (stat(domain, &st) == -1) {
					mkdir (domain, 0777);
				}
				char writepipe[LENGTH];
				char readpipe[LENGTH];
				sprintf(writepipe,"%s/%s_WR", domain, identifier);
				sprintf(readpipe,"%s/%s_RD", domain, identifier);
				// Creating pipes	
				if (mkfifo (writepipe, 0777) == -1) {
					//Couldnt create write pipe!!! 
				}
				if (mkfifo (readpipe, 0777) == -1) {
					//Couldnt create read pipe!!! 
				}

				int result = fork ();
				if (result == 0) {
					//Cilent handler
					client_handler (readpipe, writepipe, identifier_read, domain_read, identifier, domain) ;
				}
			} else {
				//Parent
			}
		}
		close (gevent);
	}	
}