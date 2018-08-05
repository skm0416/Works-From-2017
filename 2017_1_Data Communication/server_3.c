#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<net/if.h> 
#include<sys/ioctl.h>

#define PORT 7788
#define BUFSIZE 1024
#define POLYNOMIAL 0x04c11db7L

int sockfd;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
unsigned char receive_buffer[BUFSIZE];
unsigned char send_buffer[BUFSIZE];
unsigned char data_send_buffer[500];
int client_length;
int receive_length;
char *IP_address;
unsigned char Destination[6];
unsigned char Source[6]="123456";
unsigned char Length[2]={0,0};
unsigned char DSAPSSAP[2]={0,0};
unsigned char Control[2]={0,0};
unsigned char CRC[4];
unsigned int SABME=246;//11110110
unsigned int UA=198;//11000110
unsigned int ACKRR=128;//10000000
unsigned int ACKREJ=144;//10010000
unsigned int N_S=0;
unsigned int N_R=0;
int ifyousendmessage=0;
int havetoack=0;
int length;
int control_length=0;
unsigned long crc;

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

void make_format(unsigned char* data)
{
	strcpy(send_buffer,Destination);
	memcpy(send_buffer,Destination,6);
	memcpy(&send_buffer[6],Source,6);
	length=strlen(data)+21;
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

int Check_CRC(unsigned char* data)
{
	memmove(CRC,&receive_buffer[receive_length-4],4);
	return 1;
}

void *receive_message()
{
	while(1)
	{
		client_length=sizeof(client_address);
		receive_length=recvfrom(sockfd,receive_buffer,BUFSIZE-1,0,(struct sockaddr*)&client_address,&client_length);
		N_R++;
		IP_address=inet_ntoa(client_address.sin_addr);
		if(Check_CRC(receive_buffer)!=1)
		{
			printf("CRC Error Detected\n");
			Control[0]=ACKREJ;
			Control[1]=N_R;
			control_length=2;
			strcpy(data_send_buffer,Control);
			memcpy(data_send_buffer,Control,control_length);
			make_format(data_send_buffer);
			sendto(sockfd,send_buffer,length,0,(struct sockaddr*)&client_address,sizeof(client_address));
			N_S++;
			printf("Reply ACK-REJ to CRC-ERRORED message from %s port %d\n",IP_address,ntohs(client_address.sin_port));
		}
		else if(receive_buffer[16]==SABME)
		{
			memcpy(Destination,&receive_buffer[6],6);
			Control[0]=UA;
			control_length=1;
			strcpy(data_send_buffer,Control);
			memcpy(data_send_buffer,Control,control_length);
			make_format(data_send_buffer);
			sendto(sockfd,send_buffer,length,0,(struct sockaddr*)&client_address,sizeof(client_address));
			N_S++;
			printf("Reply UA Message to SABME message from %s port %d\n",IP_address,ntohs(client_address.sin_port));
		}
		else if(receive_buffer[16]<128)
		{
			printf("Received message from %s port %d : %s", IP_address,ntohs(client_address.sin_port),&receive_buffer[18]);
			havetoack=1;
		}
		usleep(100000);
	}
}

void *send_message()
{
	while(1)
	{
		if(havetoack==1)
		{
			Control[0]=ACKRR;
			Control[1]=N_R;
			control_length=2;
			strcpy(data_send_buffer,Control);
			memcpy(data_send_buffer,Control,control_length);
			make_format(data_send_buffer);
			printf("Reply ACK-RR to message from %s port %d\n",IP_address,ntohs(client_address.sin_port));
			sendto(sockfd,send_buffer,length,0,(struct sockaddr*)&client_address,sizeof(client_address));
			N_S++;
			havetoack=0;
		}
	}
}


int main()
{	
	pthread_t threads[2];
	int a=1;
	sockfd=socket(PF_INET, SOCK_DGRAM, 0);
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

	memset(&server_address,0,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT);
	bind(sockfd,(struct sockaddr*)&server_address, sizeof(server_address));
	pthread_create(&threads[0],NULL,receive_message,(void *)&a);
	pthread_create(&threads[1],NULL,send_message,(void *)&a);
	
	pthread_join(threads[0], (void*)&a);
	pthread_join(threads[1], (void*)&a);
}


