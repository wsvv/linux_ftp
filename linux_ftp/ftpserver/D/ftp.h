#include "ftp.h"

//接收消息
void receive_message(int ctrl_fd) {
    int i, num_read;
    char buffer[BUF_SIZE];
    read(ctrl_fd, &buffer,sizeof(buffer));
    /*
    for(i=0; i<BUF_SIZE-1; i++) {

        if((num_read = ) == -1) {

            perror("Error reading from control socket\n");
            close(ctrl_fd);
            exit(EXIT_FAILURE);
        }
        if(num_read <= 0)
        {
            break;
        }
        printf("%d\n",num_read);
        //printf("%d\n", num_read);
        //printf("%s\n",&buffer[i-(strlen(PROMPT)-2)]);
        if(strncmp(&buffer[i], PROMPT, strlen(PROMPT)) == 0) {
            buffer[i] = '\0';
            break;
        }
    //printf("%d\n", num_read);
    }
    */
    printf("read2:%d\n", num_read);
    printf("%s", buffer);
    /*
    if(num_read == 0) {

        close(ctrl_fd);
        exit(EXIT_SUCCESS);
    }
    */

}

//发送消息
void send_message(int socket_fd, char * message) {
    int length = strlen(message);

    if(write(socket_fd, message, length) != length) {
        perror("Error writing message");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

//获取用户输入
void get_request(int ctrl_fd, char * response) {
    printf("ftp>");
    bzero(response,BUF_SIZE);
    if(fgets(response, BUF_SIZE, stdin) == NULL) {
        perror("Error reading user input");
        exit(EXIT_FAILURE);
    }
}

//处理用户命令
void handle_request(struct sockaddr_in *addr, char * response){
    response[strlen(response) - 1] = '\0';
    printf("Input Commend is (%s) \n",response);
    if(strncmp(response, "exit",4) == 0)
    {
        response_exit();
        exit(0);   //结束进程
    }

}

//responese_exit
void response_exit()
{
    printf("See u next time!\n");
}