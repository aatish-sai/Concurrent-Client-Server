#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void cleanup_child(int signal){
	wait(NULL);
}

void main(){

	signal(SIGCHLD,cleanup_child);

	int sockfd,newsockfd;
	int clilen;
	struct sockaddr_in cli_addr,serv_addr;

	int i;
	char buf[100];

	//int num=0;

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Cannot create socket\n");
		exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(6000);

	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
		printf("Unable to bind local address\n");
		exit(0);
	}

	listen(sockfd,5);

	while(1){
		//num++;
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);

		if (newsockfd<0)
		{
			printf("Accept error\n");
			exit(0);
		}

		if(fork() == 0){
			close(sockfd);
			strcpy(buf,"Message from server");
			send(newsockfd,buf,strlen(buf)+1,0);

			for(i=0;i<100;i++)
				buf[i] = '\0';

			recv(newsockfd,buf,100,0);
			//printf("Message form client no %d\n",num);
			printf("%s\n", buf);

			close(newsockfd);
			exit(0);
		}
	}
}
