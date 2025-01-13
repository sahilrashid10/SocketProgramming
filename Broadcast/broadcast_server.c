#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BROADCAST_IP "255.255.255.255"
#define PORT 22000
#define MESSAGE "Broadcast Message"

int main(){
	int sockfd;
	struct sockaddr_in broadaddr;
	const int broadcast_perm=1;
	socklen_t len=sizeof(broadaddr);
	//len=sizeof(broadaddr);
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd<0)
	{
		perror("Socket Creation failed");
		exit(1);
	}
	
	if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&broadcast_perm,sizeof(broadcast_perm))<0)
	{
		perror("Setsockopt failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&broadaddr,0,sizeof(broadaddr));
	broadaddr.sin_family=AF_INET;
	broadaddr.sin_addr.s_addr=inet_addr(BROADCAST_IP);
	broadaddr.sin_port=htons(PORT);
	
	if(sendto(sockfd,MESSAGE,strlen(MESSAGE),MSG_CONFIRM,(struct sockaddr*)&broadaddr,len)<0)
	{
		perror("Sendto failed");
		exit(EXIT_FAILURE);
	}
	
	printf("Message sent: %s\n",MESSAGE);
	
	close(sockfd);
	return 0;
}

