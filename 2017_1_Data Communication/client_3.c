#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/ioctl.h>
#include<net/if.h> 

#define POLYNOMIAL 0x04c11db7L
#define BUFSIZE 1024

int sockfd;
int ifyousendmessage=0;
int havetoack=0;
int count=0;
int control_length=0;
struct sockaddr_in server_address;
unsigned char send_buffer[BUFSIZE];
unsigned char message_send_buffer[496];
unsigned char data_send_buffer[500];
unsigned char receive_buffer[BUFSIZE];
unsigned char Destination[6]={0,0,0,0,0,0,};
unsigned char Source[6]="123456";
unsigned char Length[2]={0,0};
unsigned char CRC[4]="4321";
unsigned char DSAPSSAP[2]={0,0};
unsigned char Control[2]={0,0};
unsigned int N_S=0;
unsigned int N_R=0;
unsigned int SABME=246;//11110110;
unsigned int UA=198;//11000110
unsigned int ACKRR=128;//10000000
unsigned int ACKREJ=144;//10010000
int data_length;
int server_length;
int receive_length;
int length;
int retry_count=0;
unsigned long crc;
pthread_t threads[2];

static unsigned long crc_table[256];


/* generate the table of CRC remainders for all possible bytes */
void gen_crc_table()
{
	register int i, j;
	register unsigned long crc_accum;

	for(i=0; i<256; i++)
	{
		crc_accum = ((unsigned long) i << 24);
		for(j=0; j<8; j++)
		{
			if(crc_accum & 0x80000000L)
				crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
			else
				crc_accum = (crc_accum << 1);
		}
		crc_table[i] = crc_accum;

	}
	return;
}


/* update the CRC on the data block one byte at a time */
unsigned long update_crc(unsigned long crc_accum, char *data_blk_ptr,int data_blk_size)
{
	register int i, j;

	for(j=0; j<data_blk_size; j++)
	{
		i = ((int)(crc_accum >> 24) ^ *data_blk_ptr++) & 0xff;
		crc_accum = (crc_accum << 8) ^ crc_table[i];
	}
	return crc_accum;
}

int Check_CRC(unsigned char* data)
{
	memmove(CRC,&receive_buffer[receive_length-4],4);
	return 1;
}

void make_format(unsigned char* data)
{
	strcpy(send_buffer,Destination);
	memcpy(send_buffer,Destination,6);
	memcpy(&send_buffer[6],Source,6);
	length=data_length+21;
	Length[0]=length/256;
	Length[1]=length%256;
	memcpy(&send_buffer[12],Length,2);
	memcpy(&send_buffer[14],DSAPSSAP,2);
	memcpy(&send_buffer[16],data,length-20);
	crc=update_crc(0,send_buffer,length-4);
	send_buffer[length-4]== (crc & 0xFF000000L) >> 24;
	send_buffer[length-3] = (crc & 0x00FF0000L) >> 16;
	send_buffer[length-2] = (crc & 0x0000FF00L) >> 8;
	send_buffer[length-1] = (crc & 0x000000FFL);
}

void *receive_message()
{
	while(1)
	{
		recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&server_address,&server_length);
		N_R++;
		if(Check_CRC(receive_buffer)!=1)
		{	
			printf("CRC Error Detected, send message again\n");
			sendto(sockfd, send_buffer,length,0, (struct sockaddr*)&server_address, sizeof(server_address));
			N_S++;
		}
		else if(receive_buffer[16]==ACKREJ)
		{
			printf("ACK-REJ received, send message again\n");
			sendto(sockfd, send_buffer,length,0, (struct sockaddr*)&server_address, sizeof(server_address));
			N_S++;
		}
		else if(receive_buffer[16]==ACKRR)
		{
			printf("ACK-RR received, please enter next message : ");
			ifyousendmessage=0;
		}
		usleep(100000);
	}
}

void *send_message()
{	
	printf("please enter next message : ");
	while(1)
	{
		if(ifyousendmessage==1)
		{
			if(count>30)
			{
				if(retry_count>3)
				{
					printf("Failed to send message, please enter next message : ");
					retry_count=0;
					count=0;
					ifyousendmessage=0;
				}
				else
				{
					printf("ACK not received, send message again\n");
					sendto(sockfd, send_buffer,length,0, (struct sockaddr*)&server_address, sizeof(server_address));
					N_S++;
					count=0;
					retry_count++;
				}
			}
			else
			{
				count++;
				usleep(100000);
			}
		}
		else
		{
			fgets(message_send_buffer,BUFSIZE,stdin);
			Control[0]=N_S;
			Control[1]=N_R;
			control_length=2;
			data_length=strlen(message_send_buffer)+3;
			strcpy(data_send_buffer,Control);
			memcpy(&data_send_buffer[control_length],message_send_buffer,strlen(message_send_buffer)+1);
			make_format(data_send_buffer);
			sendto(sockfd, send_buffer,length,0, (struct sockaddr*)&server_address, sizeof(server_address));
			N_S++;
			ifyousendmessage=1;
			usleep(100000);
		}
	}
}


int main()
{	
	char IP_address[20];
	int a=1;
	int port;
	unsigned long add;
	int success=0;
	gen_crc_table();

	struct ifreq ifr;
	struct ifconf ifc;
	char buf[1024];
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) { /* handle error*/ };
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }
	struct ifreq* it = ifc.ifc_req;
	const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
	for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    break;
                }
            }
        }
        else { /* handle error */ }
	}
	memcpy(Source, ifr.ifr_hwaddr.sa_data, 6);

	while(success==0)
	{
		printf("please input target IP : ");
		scanf("%s",IP_address);
		printf("please input target port : ");
		scanf("%d",&port);
		getchar();
		
		sockfd=socket(PF_INET, SOCK_DGRAM, 0);
		memset(&server_address,0,sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_port=htons(port);
		server_address.sin_addr.s_addr=inet_addr(IP_address);	 

		Control[0]=SABME;
		control_length=1;
		data_length=0;
		strcpy(data_send_buffer,Control);
		memcpy(data_send_buffer,Control,control_length);
		make_format(data_send_buffer);
		server_length=sizeof(server_address);
		sendto(sockfd, send_buffer, length,0, (struct sockaddr*)&server_address, sizeof(server_address));
		N_S++;
		receive_length=recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&server_address,&server_length);
		N_R++;
		if(Check_CRC(receive_buffer)!=1)
		{	
			printf("CRC Error Detected, send message again\n");
			sendto(sockfd, send_buffer,length,0, (struct sockaddr*)&server_address, sizeof(server_address));
			N_S++;
		}
		else if(receive_buffer[16]==UA)
		{
			printf("SABME-UA Connection Successed\n");
			memcpy(Destination,&receive_buffer[6],6);
			success=1;
		}
		else
			printf("SABME-UA Connection Failed\n");
	}
	pthread_create(&threads[0],NULL,receive_message,(void *)&a);
	pthread_create(&threads[1],NULL,send_message,(void *)&a);
	
	pthread_join(threads[0], (void*)&a);
	pthread_join(threads[1], (void*)&a);
}
