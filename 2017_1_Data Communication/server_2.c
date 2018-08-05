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
char ack[3]="aCk";	
struct sockaddr_in server_address;
struct sockaddr_in client_address;
char receive_buffer[BUFSIZE];
char send_buffer[BUFSIZE];
int client_length;
int receive_length;
char *IP_address;
int ifyousendmessage=0;
int havetoack=0;
int count=0;
int connection=0;

void *receive_message()
{
	while(1)
	{
		client_length=sizeof(client_address);
		receive_length=recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&client_address,&client_length);
		connection=1;
		receive_buffer[receive_length]='\0';
		IP_address=inet_ntoa(client_address.sin_addr);
		if(receive_buffer[0]!='\0')
		{
			if(strncmp(receive_buffer,ack,3)==0)
			{
				ifyousendmessage=0;
				receive_buffer[0]='0';
			}
			else
			{
			printf("Received message from %s port %d : %s", IP_address,ntohs(client_address.sin_port), receive_buffer);
			sendto(sockfd,ack,strlen(ack),0,(struct sockaddr*)&client_address,sizeof(client_address));
			receive_buffer[0]='\0';
			}
		}
	}
}

void *send_message()
{
	printf("Don't send Message until client connect\n");
	while(connection==0);
	while(1)
	{
		if(ifyousendmessage==1)
		{
			if(count>50)
			{	
				printf("time out!! try again\n");
				if(sendto(sockfd, send_buffer, strlen(send_buffer),0, (struct sockaddr*)&client_address, sizeof(client_address))!=strlen(send_buffer))
				{
					perror("socket send error");
					exit(1);
				}
				count=0;
			}
			else
			{
				count++;
				usleep(100000);
			}
		}
		else
		{
			fgets(send_buffer,BUFSIZE,stdin);
			if(sendto(sockfd, send_buffer, strlen(send_buffer),0, (struct sockaddr*)&client_address, sizeof(client_address))!=strlen(send_buffer))
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


