# linux_ftp

实现一个FTP服务系统  
具体：基于客户/服务器交互模式，采用TCP/IP通信协议，SOCKET套接字 Pthread 实现以支持远程文件传输的客户/服务器软件，支持文件的上传和下载。其中客户端软件命名为myftp，服务器软件命名为ftpserver  

服务器管理员登录  
![image](https://user-images.githubusercontent.com/51820921/144196515-d62ed711-52c6-417f-aa7f-2ecf8f97e66a.png)  
客户端登录     输入userinfo.txt 里的账户密码才能登陆  
  
![image](https://user-images.githubusercontent.com/51820921/144196562-abcec496-c9a0-4dc6-9022-c808bd8934ca.png)  
  
服务端功能展示			（kill未完成）支持同时处理多个客户端连接  
  
 ![image](https://user-images.githubusercontent.com/51820921/144196834-f5679a88-e33d-4c31-b03b-8043f7668b78.png)  
  
客户端功能展示  

pwd,Lpwd    显示服务端/客户端当前所在路径  
  
 ![image](https://user-images.githubusercontent.com/51820921/144196847-3f58fe66-4816-4eec-9545-f679f5ae4b1d.png)
   
Ls/dir	显示服务端/客户端当前路径下的文件 

![image](https://user-images.githubusercontent.com/51820921/144196880-d4de329c-aa24-44ab-a4f9-3965d186426d.png)  
  
CD,LCD    更改服务器/客户端的路径  
  
![image](https://user-images.githubusercontent.com/51820921/144196898-96d5e2af-374e-49df-a1be-5b6189f8e86c.png)  
  
Mkdir,Lmkdir  在服务器/客户端当前路径创建指定文件夹  
  
 ![image](https://user-images.githubusercontent.com/51820921/144197059-f3b89466-8a1f-45fb-aae2-b310588e4e0b.png)  
   

Rmdir，Lrmdir 在服务器/客户端当前路径删除指定文件夹（如有文件一并删除）  
 ![image](https://user-images.githubusercontent.com/51820921/144197094-8e495b57-6d26-4557-ab96-b402ed2adbcb.png)  
  

Put/mput  从客户端路径上传文件到服务器路径  
![image](https://user-images.githubusercontent.com/51820921/144197116-d39c680d-58bc-4e95-8020-c77d1ef6d327.png)  
  
Get/mget		从服务器路径下载文件到客户端路径  
   ![image](https://user-images.githubusercontent.com/51820921/144197164-ff9aa4ae-ae15-4b96-aac8-f624cc122bb3.png)  
![image](https://user-images.githubusercontent.com/51820921/144197174-f13b0e13-6b9c-47ef-aa10-0a7a2ba09a0e.png)  
  
