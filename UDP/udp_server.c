#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server!";
	struct sockaddr_in servaddr,clientaddr;
	
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socet creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr,0,sizeof(servaddr));
	memset(&clientaddr,0,sizeof(clientaddr));
	
	
	servaddr.sin_family= AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	if(bind(sockfd,(const struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		perror("Bind failure");
		exit(EXIT_FAILURE);
		
	}
	
	int len,n;
	len=sizeof(clientaddr);
	
	n=recvfrom(sockfd,(char*) buffer,MAXLINE,MSG_WAITALL,(struct sockaddr*)&clientaddr,&len);
	printf("Hello message sent");
	
	return 0;
	
}
