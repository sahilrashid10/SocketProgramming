#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

int main()
{
	char str[100];
	char send_msg[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	
	//bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(22000);
	
	bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	listen(listen_fd,10);
	
	//while(1)
	//{
		comm_fd=accept(listen_fd,(struct sockaddr*)NULL,NULL);
		while(1)
		{
		
			//bzero(str,100);
			
			recv(comm_fd,str,100,0);
			if(strcmp(str,"exit")==0) {break;}
			printf("Connected, message from client: %s",str);
			//send(comm_fd,str,strlen(str),0);
			
			printf("Send message to client: ");
			fgets(send_msg,100,stdin);
			if (strcmp(send_msg,"exit")==0) {break;}
			
			send(comm_fd,send_msg,strlen(send_msg),0);
		}
		close(comm_fd);
		close(listen_fd);
		return 0;
	//}
}
