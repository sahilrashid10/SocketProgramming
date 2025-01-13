#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

struct in_addr local;
struct sockaddr_in groupSock;
int sd;
int len;
//char buffer[1000];
char buffer[1024]="hello";

int main(int argc, char* argv[])
{
	sd=socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0)
	{
		perror("Opening datagram socket error");
		exit(EXIT_FAILURE);
	}
	
	memset((char*)&groupSock,0,sizeof(groupSock));
	groupSock.sin_family=AF_INET;
	groupSock.sin_port=htons(5555);
	groupSock.sin_addr.s_addr=inet_addr("225.1.1.1");
	printf("Before loopch");
	{
	char loopch=1;
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0) {
		perror("setting IP_MULTICAST_LOOP:");
		close(sd);
		exit(EXIT_FAILURE);
	}
	}
	printf("Before inet_addr");
	local.s_addr = inet_addr("127.0.0.1");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&local, sizeof(local)) < 0) {
		perror("setting local interface");
		exit(EXIT_FAILURE);
	}
	printf("Before sendto");
	//printf("Enter Message: ");
	//fgets(buffer,1000,stdin);
	//len=strlen(buffer);
	//buffer[len]='\0';
	len=sizeof(buffer);
	
	if (sendto(sd, buffer, len, 0,(struct sockaddr*)&groupSock,sizeof(groupSock)) < 0)
	{
		perror("sending datagram message");
	}
	printf("Sent");
	close(sd);
}
