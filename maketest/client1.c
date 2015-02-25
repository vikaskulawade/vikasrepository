#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void error(char *msg)
{
        perror(msg);
        exit(1);
}
int main(int argc , char *argv[])
{
        int sock,length,n;
        struct sockaddr_in server, from;
	struct hostent *hp;
        char buff[256];
	int num;
        if(argc!=3)
        {
                printf("Usage Server Port \n");
                exit(1);
        }
        sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		error("socket");
	}
	server.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
        if(hp==0)
        {
                error("Unkown host");
        }
	bcopy((char *)hp->h_addr,(char *)&server.sin_addr,hp->h_length);
        server.sin_port = htons(atoi(argv[2]));
	length=sizeof(struct sockaddr_in);
	printf("please enter the message");
	bzero(buff,256);
	//scanf("%d",&num);
	fgets(buff,255,stdin);
	n=sendto(sock,buff,256,0,&server,length);
	if(n<0)
	{
		error("send to");
	}
	bzero(buff,256);
	n=recvfrom(sock,buff,256,0,&from,&length);
        if(n<0)
        {
                error("receve from");
        }
	write(1,"Got An ACK",11);
	write(1,buff,n);
}
                                                                                                                     
