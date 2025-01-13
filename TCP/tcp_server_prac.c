//Receive Messages and Send Echo Message
#include<stdio.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
 
int main(){
    char str[100];
    char send_msg[100];
    char* ip;
    int listen_fd, conn_fd, port;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    listen_fd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 
    bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(listen_fd,10);
 
    while(1){
        len=sizeof(cliaddr);
        conn_fd=accept(listen_fd,(struct sockaddr*)&cliaddr,&len);
        ip=inet_ntoa(cliaddr.sin_addr);
        printf("Client IP: %s\n",ip);
        port=ntohs(cliaddr.sin_port);
        printf("Client Port: %d\n",port);
        while(1)
        {
            
            int i=0;
            
            recv(conn_fd,str,100,0);
            int len_str=strlen(str);
            str[len_str]='\0';
            printf("Client: %s\n",str);
            
            while(str[i]!='\0')
            {
                send_msg[i]=str[len_str-i-1];
                i++;
            }
            send_msg[len_str]='\0';
            send(conn_fd,send_msg,strlen(send_msg),0);
            bzero(str,100);
            printf("Ulta sent\n");
        }
        close(conn_fd);
    }
    close(listen_fd);
    return 0;
}
