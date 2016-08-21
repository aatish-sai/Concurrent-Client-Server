#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(){
	int sockfd;
	struct sockaddr_in serv_addr;

	int i;
	char buf[100];

		if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
			printf("Unable to create socket\n");
			exit(0);
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr("192.168.1.6");
		serv_addr.sin_port = htons(6000);

		if ((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0)
		{
			printf("Unable to connect to server\n");
			exit(0);
		}

		for(i=0;i<100;i++)
			buf[i] = '\0';

		recv(sockfd,buf,100,0);
		printf("%s\n", buf);

		strcpy(buf,"message from client");
		send(sockfd,buf,strlen(buf)+1,0);

		close(sockfd);
}