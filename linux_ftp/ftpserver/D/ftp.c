#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256
#define PROMPT ">"

void receive_message(int ctrl_fd);

void get_request(int ctrl_fd, char * response);

void handle_request(struct sockaddr_in *addr, char * response);