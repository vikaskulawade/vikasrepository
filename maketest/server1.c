#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include<ctype.h>
#include <arpa/inet.h>
void error(char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc , char *argv[])
{
	int sock,length,fromlen,n,num,i=0;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buff[14],str[14];
	if(argc<2)
	{
		fprintf(stderr,"Error ,No Port provided\n");
		exit(0);
	}
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		error("Opening Sock");
	}
	length=sizeof(server);
	bzero(&server,length);
	server.sin_family = AF_INET;
  	server.sin_addr.s_addr = htonl(INADDR_ANY);//
  	server.sin_port = htons(atoi(argv[1]));
	if(bind(sock,(struct sockaddr*)&server,length)<0)
	{
		error("binding");
	}
	fromlen=sizeof(struct sockaddr_in );
	while(1)
	{
		n=recvfrom(sock,buff,14,0,(struct sockaddr*)&from,&fromlen);
		//num=atoi(buff);
		if(n<0)
		{
			error("receve from");
		}
		write(1,"Receved datagram",16);
		//for(i=0;i<strlen(buff);i++)
	        {
			//num=((int)(*(buff+i)));
			//strcpy(str,buff);
			int len = strlen(buff) -1;
			buff[len] = 0;
			num=atoi(buff);
			i=i+num;
			printf("\n\t%d\n",i);
			//printf("\n\t%d\n",strlen(buff));

		}
		//write(1,buff,n);
	   	n=sendto(sock,"Got Your Msg",13,0,(struct sockaddr *)&from,fromlen);
		if(n<0)
		{
			error("Send to");
		}
	}
}	
	

	


