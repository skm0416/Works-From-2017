#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define PORT 7788
#define BUFSIZE 1024

int sockfd;	
struct sockaddr_in server_address;
struct sockaddr_in client_address;
char receive_buffer[BUFSIZE];
int client_length;
int receive_length;
char *IP_address;

void *receive_message()
{
	while(1)
	{
		client_length=sizeof(client_address);
		if((receive_length=recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&client_address,&client_length))==-1)
		{
			perror("socket receive error");
			exit(1);
		}
		receive_buffer[receive_length]='\0';
		IP_address=inet_ntoa(client_address.sin_addr);
		printf("Received message from %s port %d : %s", IP_address,ntohs(client_address.sin_port), receive_buffer);
	}
}

void *send_message()
{
	while(1)
	{
		if(receive_buffer[0]!='\0')
		{
			if(sendto(sockfd,receive_buffer,receive_length,0,(struct sockaddr*)&client_address,sizeof(client_address))!=receive_length)
			{
				perror("socket send error");
				exit(1);
			}
			receive_buffer[0]='\0';
		}
	}
}


int main()
{	
	pthread_t threads[2];
	int a=1;
	if((sockfd=socket(PF_INET, SOCK_DGRAM, 0))==-1)
	{
		perror("socket create error");
		exit(1);
	}

	memset(&server_address,0,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT);
	if(bind(sockfd,(struct sockaddr*)&server_address, sizeof(server_address))==-1)
	{
		perror("socket bind error");
		exit(1);
	}
	receive_buffer[0]='\0';
	pthread_create(&threads[0],NULL,receive_message,(void *)&a);
	pthread_create(&threads[1],NULL,send_message,(void *)&a);
	
	pthread_join(threads[0], (void*)&a);
	pthread_join(threads[1], (void*)&a);
}


