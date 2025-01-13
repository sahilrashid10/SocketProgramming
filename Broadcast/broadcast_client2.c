#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 22000
#define BUFFER_SIZE 100
#define IP "127.0.0.1"

int main()
{
	int sockfd;
	struct sockaddr_in recvaddr2, cliaddr2;
	char buffer[BUFFER_SIZE];
	socklen_t addrlen=sizeof(cliaddr2);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
		perror("Socket creation failed");
		exit(1);
	}
	
	int option=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option))<0){
		perror("REUSE ERR");
		exit(EXIT_FAILURE);
	}
	
	memset(&recvaddr2,0,sizeof(recvaddr2));
	recvaddr2.sin_family=AF_INET;
	recvaddr2.sin_addr.s_addr=htonl(INADDR_ANY);
	recvaddr2.sin_port=htons(PORT);
	
	
	if(bind(sockfd,(struct sockaddr*)&recvaddr2,sizeof(recvaddr2))<0)
	{
		perror("Bind fail error se");
		exit(1);
	}

	
	printf("Waiting for messages to be broadcasted....\n");
	
	while(1)
	{
		int recvlen=recvfrom(sockfd,buffer,BUFFER_SIZE-1,MSG_WAITALL,(struct sockaddr*)&cliaddr2,&addrlen);
		if(recvlen<0)
		{
			perror("Recvfrom failed");
			exit(EXIT_FAILURE);
		}
		buffer[recvlen]='\0';
		
		printf("Received message: %s\n",buffer);
		
		
	}
	close(sockfd);
	return 0;
}
