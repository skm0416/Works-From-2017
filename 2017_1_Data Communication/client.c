#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define BUFSIZE 1024

int sockfd;
int ifyousendmessage=0;
int count=0;
struct sockaddr_in server_address;
char send_buffer[BUFSIZE];
char receive_buffer[BUFSIZE];
int server_length;
int receive_length;
pthread_t threads[2];

void *receive_message()
{
	while(1)
	{
		server_length=sizeof(server_address);
		if((receive_length=recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&server_address,&server_length))!=strlen(send_buffer))
		{
			perror("socket receive error");
			exit(1);
		}
		receive_buffer[receive_length]='\0';
		if(receive_buffer[0]!='\0'){
			ifyousendmessage=0;
			printf("echo message : %s", receive_buffer);
			receive_buffer[0]='\0';
		}
	}
}

void *send_message()
{	
	while(1)
	{
		if(ifyousendmessage==1)
		{
			if(count>5)
			{	
				printf("time out!! try again\n");
				if(sendto(sockfd, send_buffer, strlen(send_buffer),0, (struct sockaddr*)&server_address, sizeof(server_address))!=strlen(send_buffer))
				{
					perror("socket send error");
					exit(1);
				}
				count=0;
			}
			else
			{
				count++;
				sleep(1);
			}
		}
		else
		{
			fgets(send_buffer,BUFSIZE,stdin);
			if(sendto(sockfd, send_buffer, strlen(send_buffer),0, (struct sockaddr*)&server_address, sizeof(server_address))!=strlen(send_buffer))
			{
				perror("socket send error");
				exit(1);
			}
			ifyousendmessage=1;
			count=0;
		}
	}
}


int main()
{	
	char IP_address[20];
	int a=1;
	int port;
	unsigned long add;
	printf("please input target IP : ");
	scanf("%s",IP_address);
	printf("please input target port : ");
	scanf("%d ",&port);
	if((sockfd=socket(PF_INET, SOCK_DGRAM, 0))==-1)
	{
		perror("socket create error");
		exit(1);
	}

	memset(&server_address,0,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port=htons(port);
	server_address.sin_addr.s_addr=inet_addr(IP_address);	 

	receive_buffer[0]='\0';
	pthread_create(&threads[0],NULL,receive_message,(void *)&a);
	pthread_create(&threads[1],NULL,send_message,(void *)&a);
	
	pthread_join(threads[0], (void*)&a);
	pthread_join(threads[1], (void*)&a);
}


