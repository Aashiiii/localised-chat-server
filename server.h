#ifndef SERVER_H
#define SERVER_H
#endif
#define LENGTH 2048
#define MESSAGE 1790
#define IDEN 256
#define PATH_LEN 514
#define SLEEP_TIME 15
#define SAY 1
#define SAYCONT 2
#define RECV 3
#define RECVCONT 4
#define DISCONNECT 7
#define PONG 6
#define PING 5
#define MAX 100000000

void receive (char* readpipe, char* writepipe, char* identifier_read, 
                char* domain_read, char* identifier, char* domain, char* buffer, 
              char* buf_receive);
void say (char* readpipe, char* writepipe, char* identifier_read, 
            char* domain_read, char* identifier, char* domain, char* buffer, 
          int cont);
void disconnect (char* writepipe, char* readpipe);
void kill_ping (int sig);
void client_handler (char* readpipe, char* writepipe, char* identifier_read, 
						char* domain_read, char* identifier, char* domain);
void kill_child (int sig);