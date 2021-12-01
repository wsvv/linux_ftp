#include<stdio.h>
#include<string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include<dirent.h>
#include <sys/stat.h>
//#include <winsock2.h>
#include <fcntl.h>
#include"unistd.h"
#include<pthread.h>

#define N 256

int usernums,onlineusernums;
int id;
char usernameList[2*N][N];

int serverControl() ;

void lrm_dir(char *path_name);

void lmk_dir(char * path_name);

int dir();

void lpwd();

void lcd(char* directory);

void cilent_commdpro(int socket,char* commd);

void cilent_get(int socket,char *commd);

void cilent_put(int socket,char *commd);

int cilentlogin(int sockfd,char *commd);

void newuserthread(void *socket);

void progress_commd(int socket);

void server_put(int socket,int file_nums,char *commd);

void server_get(int socket,int file_nums,char *commd);

void rm_dir(int socket,char *path_name);

void mk_dir(int socket,char * path_name);

void del_Files(char *dir);

int ls(int socket);

void pwd(int fd) ;

void cd(int fd, char* directory);

void sendMessage(int socket_fd, char* message);

void receive_message(int socket_fd );

int startServer(char* ipserver, int port);

int create_socket();

void bind_socket(int socket_fd, int port, char* ipserver);

void listen_socket(int socket_fd);

int accept_connetion(int socket_fd);
