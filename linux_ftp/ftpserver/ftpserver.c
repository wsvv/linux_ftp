#include <stdio.h>
#include <stdlib.h>
#include"thread.h"

int main(int argc ,char *argv[])
{

    pthread_t systemid;
    int cilentsocket,serversocket;
    char sername[N]={"admin"};
    char serpassword[N]={"admin"};
    char loginname[N]={"0"};
    char password[N]={"0"};
    char ip[20];
    int port;
    id=0;
    usernums=0;
    onlineusernums=0;

    if(argc ==2){
        printf("error");
        //ip=accuire ip;
    }else if(argc ==3){
        port=atoi(argv[2]);
        strcpy(ip,argv[1]);
        //memcpy(ip,argv[1],strlen(argv[1]));
        printf("ip:%s port:%d\n",ip,port);
    }
    else {
        printf(" ‰»Î¥ÌŒÛ");
        return 0;
    }
    serversocket=startServer(ip,port);

    // server login
    printf("please input admin name\n");
    fgets(loginname, N, stdin);
    loginname[strlen(loginname) - 1] = '\0';
    if(!strncmp(sername,loginname,5)){
        printf("please input admin password\n");
        fgets(password, N, stdin);
        password[strlen(password) - 1] = '\0';
        if(!strncmp(serpassword,password,5)){
            pthread_create(&systemid,NULL,(void *)&serverControl,NULL);
            printf("succeed login\n");
        }
        else{
            printf("admin password error!\n");
        }
    }
    else{
        printf("admin name error!\n");
    }

    while(1){
        char tmp[N];
        char tmpname[N];
        pthread_t threadid;

        if((cilentsocket=accept_connetion(serversocket))<0){
            break;
        }
        read(cilentsocket,tmp,N);
        if(cilentlogin(cilentsocket,tmp)){
            continue;
        }
        strcpy(tmpname,tmp);
        printf("%d\n",id);
        read(cilentsocket,tmp,N);
        if(cilentlogin(cilentsocket,tmp)){
            continue;
        }
        strcpy(usernameList[id],tmpname);
        printf("id %d  succed connected\n",id++);
        usernums++;
        onlineusernums++;
        if(pthread_create(&threadid,NULL,(void *)newuserthread,(void *)&cilentsocket)== -1){
            printf("pthread_create error\n");
            continue;
        }
        bzero(tmp,sizeof(tmp));
        bzero(tmpname,sizeof(tmpname));
    }
    return 0;
}


