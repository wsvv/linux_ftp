#include"thread.h"
// For Servercontrol

int serverControl() {
    char cmd[N];
    while (1)
    {
        printf("Server>");
        fgets(cmd, N, stdin);
        cmd[strlen(cmd) - 1] = '\0';  //fgets不会像gets那样自动地去掉结尾的\n，所以手动将\n位置处的值变为\0

        if (!strcmp(cmd, "count all")) {
            printf("历史系统访客数量：%d\n", usernums);
            continue;
        }else
        if (!strcmp(cmd, "count current")) {
            printf("系统在线访客数量：%d\n", onlineusernums);
            continue;
        }else
        if (!strcmp(cmd, "list")) {
            listUser();
            continue;
        }else
        if (!strcmp(cmd, "kill username")) {

            continue;
        }
        else
        if (!strcmp(cmd, "quit")) {
            quit();
            continue;
        }
        else
        if (!strcmp(cmd, "help")) {
            help();
            continue;
        }
        else {
            printf("未知命令\n"
                "输入help获得帮助\n");
        }
    }

}


// For Servercontrol
int quit(){
    printf("Quit Successful! \n");
    exit(0);
}

int listUser() {
    int i=0;
            for(;i<=id;i++){
                if(strlen(usernameList[i])!=0)
                    printf("---id:%d username:%s\n", i,usernameList[i]);
            }
}

int killUser() {

}

int help() {
    printf("count all:历史系统访客数量\n"
        "count current:当前在线访客总数\n"
        "list:显示当前在线的所有用户的用户名\n"
        "kill username:强制删除某个用户\n"
        "quit:关闭ftp服务器软件\n");
}


// For cilent

void lrm_dir(char *path_name){
    if(strlen(path_name)==0){
        printf("Wrong path name!");
        return ;
    }
    char dir[N];
    getcwd(dir, sizeof(dir));
    //将路径完整
    if(!strncmp(path_name,"/",1)){
        strcat(dir,path_name);
    }else{
        strcat(dir,"/");
        strcat(dir,path_name);
    }
    del_Files(dir);
    rmdir(dir);
    printf("succeed rmdir");
    //sendMessage(socket,"succeed\n");
    //write(sockfd,"rmdir success!",N);
    return ;
}


void lmk_dir(char * path_name){
    char dir[N];
    getcwd(dir, sizeof(dir));
    printf("%s\n",dir);
    //将路径完整
    if(!strncmp(path_name,"/",1)){
        strcat(dir,path_name);
    }else{
        strcat(dir,"/");
        strcat(dir,path_name);
    }
    if(!(dir[sizeof(dir)-1]=='/'))
        strcat(dir,"/");
    //printf("%s\n",dir );
    int i,len=strlen(dir);
    for(i=1;i<len;i++){
        if(dir[i]=='/'){
            dir[i]=0;
            if(access(dir,NULL)!=0){//查看文件夹是否存在
                if(mkdir(dir,0755)==-1){
                    printf("error");
                    perror("mkdir error");
                    //write(sockfd,"mkdir error",N);
                    return ;
                }
            }
            dir[i] = '/';
        }
    }
    //write(sockfd,"mkdir success!",N);
    //sendMessage(socket,"succeed\n");
    printf("succeed mkdir");
    return ;
}

int dir()
{
	DIR* dp;
	char show[1024];
	struct dirent* entry;
	struct stat statbuf;
	char buf[N] = "";
	getcwd(buf, sizeof(buf));
	printf("%s\n",buf);
	dp = opendir(buf);
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
			strcat(show, "dir:");
			strcat(show, entry->d_name);
			//strcat(show,"	-->dir	");
			strcat(show, "\n");
		}
		else {
			strcat(show, "file:");
			strcat(show, entry->d_name);
			//strcat(show,"	-->file	");
			strcat(show, "\n");
		}
	}
	closedir(dp);
	printf("%s\n",show);
	//sendMessage(socket,show);
	bzero(show,sizeof(show));
	bzero(buf,sizeof(show));
	return 1;
}

void lpwd() {

	char dir[N];
	if (getcwd(dir, sizeof(dir)) == NULL) {
		printf("getcwd failed\n");
		//sendMessage(fd,"getcwd failed\n");
		return -1;
	}
	printf("%s\n", dir);
	//sendMessage(fd,dir);
	memset(dir, 0, sizeof(dir));
	return;

}


void lcd(char* directory) {
	int i;


	//printf("%s\n",directory);
	i = chdir(directory);

	printf("succeed cd\n");
    return ;
}

void cilent_commdpro(int socket,char* commd){
    sendMessage(socket,commd);
    receive_message(socket);
    return ;
}

void cilent_get(int socket,char *commd){
    int filenums=0;
    char buffer[N];
    char fileallname[N],filename[N];
    char ret[N];
    int fd,nbytes;
    sendMessage(socket,commd);
    strcpy(fileallname,commd);
    strtok(commd," ");
    while(strtok(NULL," "))
        filenums++;
    strtok(fileallname," ");
    while(filenums){
        strcpy(filename,strtok(NULL," "));
        printf("will down %s\n",filename);
        read(socket,ret,N);
        if(ret[0]=="N"){
            printf("cant open %s\n",filename);
            return ;
        }
         if((fd=open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0){     //0644=rw-r--r--
            //printf("Open file Error!\n");
            return ;
        }
        nbytes=read(socket, buffer, N);

        while(1){
            if(write(fd, buffer, nbytes) < 0){
                printf("Write Error! \n");
                close(fd);
                return ;
            }
            if(nbytes<N)
                break;
            else{
                nbytes = read(socket,buffer,N);
            }
        }
        write(socket,"Y",N);
        printf("succeed send Y\n");
        bzero(buffer,sizeof(buffer));
        bzero(ret,sizeof(ret));
        close(fd);
        filenums--;
        printf("succeed receive %s\n",filename);
    }
    return ;
}

void cilent_put(int socket,char *commd){
    int filenums=0;
    char fileallname[N],filename[N];
    char ret[N];
    int fd,nbytes;
    char buffer[N];
    sendMessage(socket,commd);

    strcpy(fileallname,commd);
    strtok(commd," ");
    while(strtok(NULL," "))
        filenums++;
    strtok(fileallname," ");

    while(filenums){

        strcpy(filename,strtok(NULL," "));
        printf("put file %s\n",filename);
        if((fd=open(filename, O_RDONLY)) < 0){
                printf("Open Error!%s\n",filename);
                break;
        }
        while((nbytes=read(fd, buffer, N)) > 0){
            if(write(socket, buffer, nbytes) < 0){
                printf("Write Error!\n");
            }
        }

        read(socket,buffer,N);
        printf("succeed read\n");
        filenums--;
        close(fd);
        bzero(buffer,sizeof(buffer));
        printf("succeed send message %s\n",filename);
        printf("num %d\n",filenums);
    }
    return ;
}

// For server

int cilentlogin(int sockfd,char *commd)
{
    int fd, nbytes,error=0;
    char buffer[30];
    if((fd = open("userinfo.txt",O_RDONLY,30))<0){
        printf("Open user File Error\n");
        write(sockfd,"user error",N);
        exit(1);
    }
    read(fd,buffer,30);
        //printf("%s\n", buffer);
    if(strstr(buffer,commd)){
            sendMessage(sockfd,"Y");
            return 0;
    }
    sendMessage(sockfd,"N");
    bzero(commd,N);
    return 1;
}

void newuserthread(void *socket){
    int fd=*((int*)socket);
    progress_commd(fd);
    close(fd);
    close(socket);
    onlineusernums--;
    return;


}

void progress_commd(int socket){
    char recvcommd[N];

    while(1){
        while(read(socket,recvcommd,N)>0){
            if(!strncmp(recvcommd,"cd",2)){
                char commd[N];
                strtok(recvcommd," ");
                strcpy(commd,strtok(NULL," "));
                printf("%s\n",commd);
                cd(socket,commd);
                bzero(commd,sizeof(commd));

            }
            else if(!strncmp(recvcommd,"ls",2)){

                ls(socket);
            }
            else if(!strncmp(recvcommd,"pwd",3)){
                pwd(socket);
            }
            else if(!strncmp(recvcommd,"mkdir",5)){
                char commd[N];
                strtok(recvcommd," ");
                strcpy(commd,strtok(NULL," "));
                printf("%s\n",commd);
                mk_dir(socket,commd);
                bzero(commd,sizeof(commd));
            }
            else if(!strncmp(recvcommd,"rmdir",5)){
                char commd[N];
                strtok(recvcommd," ");
                strcpy(commd,strtok(NULL," "));
                printf("%s\n",commd);
                rm_dir(socket,commd);
                bzero(commd,sizeof(commd));
            }
            else if((!strncmp(recvcommd,"get",3))||(!strncmp(recvcommd,"mget",4))){
                int file_nums = 0;
                char commds[N];
                strcpy(commds,recvcommd);
                strtok(recvcommd," ");
                while(strtok(NULL," "))
                        file_nums++;
                server_put(socket,file_nums,commds);
                bzero(commds,sizeof(commds));
            }
            else if((!strncmp(recvcommd,"put",3))||(!strncmp(recvcommd,"mput",4))){
                int file_nums = 0;
                char commds[N];
                strcpy(commds,recvcommd);
                strtok(recvcommd," ");
                while(strtok(NULL," "))
                    file_nums++;
                server_get(socket,file_nums,commds);
                bzero(commds,sizeof(commds));
            }
            else if(!strncmp(recvcommd,"exit",4)){
                close(socket);
                //bzero(online_visitor_list[user_id],N);
                //online_visitor--;
                return ;
            }
            bzero(recvcommd,N);
        }

    }
    return ;

}

void server_put(int socket,int file_nums,char *commd){
    int fd;
    int nbytes;
    char buffer[N];
    char file_name[N];
    //printf("%s\n", commd);
    char dir[N];
    getcwd(dir, sizeof(dir));
    strtok(commd," ");
    while(file_nums){

        strcpy(file_name,strtok(NULL," "));
        printf("down %s\n", file_name);
        if((fd=open(file_name, O_RDWR)) < 0){
            //printf("Open file Error!\n");
            //printf("ftpserver>");
            buffer[0]='N';
            sendMessage(socket,buffer);

            return ;
        }
        buffer[0] = 'Y';
        if(write(socket, buffer, N) <0){
            printf("Write Error!\n");
            close(fd);
            return ;
        }
        while((nbytes=read(fd, buffer, N)) > 0){
            if(write(socket, buffer, nbytes) < 0){
                printf("Write Error!\n");
                close(fd);
                return ;
            }
        }

        read(socket,buffer,N);

        bzero(buffer,sizeof(buffer));
        file_nums--;
        printf("succeed send %s\n",file_name);
        close(fd);
    }
    return ;
}

void server_get(int socket,int file_nums,char *commd){
    int fd;
    int nbytes;
    char buffer[N];
    char file_name[N];
    strtok(commd," ");
    printf("%d\n",file_nums);
    while(file_nums){

        strcpy(file_name,strtok(NULL," "));

        printf("%s\n", file_name);
        if((fd=open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0){     //0644=rw-r--r--


            return ;
        }

        nbytes=read(socket, buffer, N);

        while(1){
            if(write(fd, buffer, nbytes) < 0){
                printf("Write Error! At commd_put 1!\n");
                close(fd);
                return ;
            }


            //printf("向%s写入%s\n", file_name,buffer);
            if(nbytes<N)
                break;
            else{
                nbytes = read(socket,buffer,N);
                //printf("%d\n", nbytes);
            }
        }

        write(socket,"Y",N);
        close(fd);
        file_nums--;
        bzero(buffer, sizeof(buffer));
        printf("succeed receive %s\n",file_name);
    }
    return ;
}

void rm_dir(int socket,char *path_name){
    if(strlen(path_name)==0){
        write(socket,"Wrong path name!",N);
        return ;
    }
    char dir[N];
    getcwd(dir, sizeof(dir));
    //将路径完整
    if(!strncmp(path_name,"/",1)){
        strcat(dir,path_name);
    }else{
        strcat(dir,"/");
        strcat(dir,path_name);
    }
    del_Files(dir);
    rmdir(dir);

    sendMessage(socket,"succeed\n");
    //write(sockfd,"rmdir success!",N);
    return ;
}

void del_Files(char *dir){
    DIR *dp; //声明一个句柄
    struct dirent *entry;
    struct stat statbuf;

    if((dp=opendir(dir))==NULL){
        //perror("opendir");
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return ;
    }
    chdir(dir);
    while((entry = readdir(dp))!=NULL){
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0){
                continue;
            }
            //printf("%*s%s/\n", depth," ",entry->d_name);
            del_Files(entry->d_name);
            remove(entry->d_name);
        }else{
            //printf("%*s%s\n",depth," ",entry->d_name );
            remove(entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);

    return ;
}

void mk_dir(int socket,char * path_name){
    char dir[N];
    getcwd(dir, sizeof(dir));
    printf("%s\n",dir);
    //将路径完整
    if(!strncmp(path_name,"/",1)){
        strcat(dir,path_name);
    }else{
        strcat(dir,"/");
        strcat(dir,path_name);
    }
    if(!(dir[sizeof(dir)-1]=='/'))
        strcat(dir,"/");
    //printf("%s\n",dir );
    int i,len=strlen(dir);
    for(i=1;i<len;i++){
        if(dir[i]=='/'){
            dir[i]=0;
            if(access(dir,NULL)!=0){//查看文件夹是否存在
                if(mkdir(dir,0755)==-1){
                    printf("error");
                    perror("mkdir error");
                    //write(sockfd,"mkdir error",N);
                    return ;
                }
            }
            dir[i] = '/';
        }
    }
    //write(sockfd,"mkdir success!",N);
    sendMessage(socket,"succeed\n");
    return ;
}

int ls(int socket)
{
	DIR* dp;
	char show[1024];
	struct dirent* entry;
	struct stat statbuf;
	char buf[N] = "";
	getcwd(buf, sizeof(buf));
	printf("%s\n",buf);
	dp = opendir(buf);
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
			strcat(show, "dir:");
			strcat(show, entry->d_name);
			//strcat(show,"	-->dir	");
			strcat(show, "\n");
		}
		else {
			strcat(show, "file:");
			strcat(show, entry->d_name);
			//strcat(show,"	-->file	");
			strcat(show, "\n");
		}
	}
	closedir(dp);
	printf("%s\n",show);
	sendMessage(socket,show);
	bzero(show,sizeof(show));
	bzero(buf,sizeof(show));
	return 1;
}

void pwd(int fd) {

	char dir[N];
	if (getcwd(dir, sizeof(dir)) == NULL) {
		printf("getcwd failed\n");
		//sendMessage(fd,"getcwd failed\n");
		return -1;
	}
	//printf("%s\n", dir);
	sendMessage(fd,dir);
	memset(dir, 0, sizeof(dir));
	return;

}


void cd(int fd, char* directory) {
	int i;


	//printf("%s\n",directory);
	i = chdir(directory);

	sendMessage(fd,"succeed cd\n");
    return ;
}




void sendMessage(int socket_fd, char* message) {

	if (write(socket_fd, message, N) != N) {
		printf("send error\n");
		close(socket_fd);
		exit(1);
	}
}

void receive_message(int socket_fd ) {
	int num_read;
	char buffer[N];
	if ((num_read = read(socket_fd, &buffer, N)) == -1) {
		perror("Error reading from control socket");
		close(socket_fd);
		exit(1);
	}
	if (num_read == 0)
		return;

	printf("%s\n", buffer);
}




int startServer(char* ipserver,int port) {
	int fd;
	fd = create_socket();
	bind_socket(fd, port, ipserver);
	listen_socket(fd);
	printf("IP:%s\n", ipserver);
	printf("PORT:%d\n", port);
	printf("ftp server start successful!\n");
	return fd;
}

int create_socket() {
	int socker_fd;
	if ((socker_fd = socket(AF_INET,SOCK_STREAM, 0)) == -1) {
		printf("create error\n");
		exit(1);
	}
	printf("create success\n");
	return socker_fd;
}

void bind_socket(int socket_fd, int port,char *ipserver) {
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr =  inet_addr(ipserver);
	address.sin_port = htons(port);
	printf("%d\n",(address.sin_addr.s_addr));
	printf("%d\n",address.sin_port);
	if (bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
		printf("bind error\n");
		close(socket_fd);
		exit(1);
	}

}

void listen_socket(int socket_fd) {
	if (listen(socket_fd, 10) <0) {
		printf("listen error\n");
		return -1;
	}
	printf("listen ok\n");
}

int accept_connetion(int socket_fd) {
	struct sockaddr_in address;
	int addressSizeof = sizeof(address);
	int cilentSocket ;
	if ((cilentSocket = accept(socket_fd, (struct sockaddr*)&address, &addressSizeof)) == -1) {
		printf("Cannot accpet New User!\n");
        return -1;
	}
	return cilentSocket;
}
