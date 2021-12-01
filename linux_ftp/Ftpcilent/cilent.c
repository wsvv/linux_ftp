#include"thread.h"
#define PROTOCOL 0


int i;


//char server[] = "username:passwd@127.0.0.1:95274";

int main(int argc, char *argv[])
{    //入参解析
    char userName[30] = { 0 };
    char passWord[30] = { 0 };
    char Ftp_ip[20];
    char server[20];
    char Ftp_port[30];
    char commd[N];
	strcpy(userName, strtok(argv[1], ":"));

	strcpy(passWord, strtok(NULL, "@"));

	strcpy(Ftp_ip, strtok(NULL, ":"));

	strcpy(Ftp_port, strtok(NULL, ":"));
	printf("%s %s %s %s  \n",userName, passWord, Ftp_ip, Ftp_port);


	//创建套字节
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, PROTOCOL)) == -1)
	{
		perror("套字节创建失败！\n");
		return -1;
	}


	//绑定（bind）
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(Ftp_port));
	addr.sin_addr.s_addr = inet_addr(Ftp_ip);

	if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        printf("Connect Error!\n");
        exit(1);
    }

    sendMessage(sockfd,userName);
    read(sockfd,commd,N);
    if(!strncmp(commd,"N",1)){
        printf("username error!\n");
        return ;
        }
    sendMessage(sockfd,passWord);
    read(sockfd,commd,N);
    if(!strncmp(commd,"N",1)){
        printf("userpassword error!\n");
        return ;
        }

    while(1){
        bzero(commd,sizeof(commd));
        printf("myftp>");
        fgets(commd,N,stdin);
        commd[strlen(commd)-1]='\0';

        if((!strncmp(commd,"mkdir",5))||(!strncmp(commd,"pwd",3))||(!strncmp(commd,"cd",2))||(!strncmp(commd,"rmdir",5))||(!strncmp(commd,"ls",2))){
            cilent_commdpro(sockfd,commd);
        }else if((!strncmp(commd,"get",3))||(!strncmp(commd,"mget",4))){
            cilent_get(sockfd,commd);
        }else if((!strncmp(commd,"put",3))||(!strncmp(commd,"mput",4))){
            cilent_put(sockfd,commd);
        }else if(!strncmp(commd,"exit",4)){
            write(sockfd,"exit",N);
            exit(0);
        }else if(!strncmp(commd,"lmkdir",6)){
            char tem[N];
            strtok(commd," ");
            strcpy(tem,strtok(NULL," "));
            printf("%s\n",tem);
            lmk_dir(tem);
            bzero(tem,sizeof(tem));
        }
        else if(!strncmp(commd,"lrmdir",6)){
            char tem[N];
            strtok(commd," ");
            strcpy(tem,strtok(NULL," "));
            printf("%s\n",tem);
            lrm_dir(tem);
            bzero(tem,sizeof(tem));
            }
        else if(!strncmp(commd,"lcd",3)){
            char tem[N];
            strtok(commd," ");
            strcpy(tem,strtok(NULL," "));
            printf("%s\n",tem);
            lcd(tem);
            bzero(tem,sizeof(tem));

            }
        else if(!strncmp(commd,"dir",3)){

                dir();
            }
        else if(!strncmp(commd,"lpwd",4)){
                lpwd();
            }

        else{
            printf("myftp>commd error\n");
        }



}
	return 0;
}

