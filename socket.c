#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXDATASIZE 1024
#define SERVERPORT  8000
#define MAXCONN_NUM  10

int main()
{
	char buf[MAXDATASIZE];
	int sockfd , new_fd , numbytes;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sin_size;
	if((sockfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	{
		perror("socket error");
		return 1;
	}
	memset(&client_addr,0,sizeof(struct sockaddr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(SERVERPORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd , (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind error");
		return 1;
	}	
	
	if(listen(sockfd , MAXCONN_NUM) == -1)
	{
		perror("listen error");
		return 1;
	}

	// the main function
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(sockfd , (struct sockaddr *)&client_addr , &sin_size);
		if(new_fd == -1)
		{
			perror("accept error");
			continue;
		}	
	//	printf("server: got connection from %s/n",inet_ntoa(client_addr.sin_addr));
		numbytes = recv(new_fd , buf , MAXDATASIZE , 0);		
		if(numbytes == -1)
		{
			perror("recv error");
			return 1;
		}
		else
		{
			buf[numbytes] = 0;
			printf("received:%s/n",buf);
			sleep(3);
		}
		printf("send: hi~~/n");
		if(send(new_fd , "hi~~" , 5 , 0) == -1)
		{
			perror("send error");
			return 1;
		}
		close(new_fd);
	}
	return 0;
} 

















