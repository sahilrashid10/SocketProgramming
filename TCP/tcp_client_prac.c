//Send Messages and Receive echo messages
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>


int main()
{
	char sendline[100], recvline[100];
	int sockfd;
	struct sockaddr_in servaddr;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	connect(sockfd,(struct sockaddr*) &servaddr,sizeof(servaddr));
	
	while(1)
	{
		bzero(sendline,100);
		bzero(sendline,100);
		while(1)
		{
			
			fgets(sendline,100,stdin);
			send(sockfd,sendline,strlen(sendline),0);
			printf("Sent message: %s\n",sendline);
			recv(sockfd, recvline,100,0);
			printf("Received Message: %s\n",recvline);
		}
		close(sockfd);
	}
	return 0;
}
		
