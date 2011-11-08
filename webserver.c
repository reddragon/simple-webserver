#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>

#define SERV_PORT "3000"
#define BACKLOG 100
int main()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	struct addrinfo hints, *res;

	int sockfd, new_fd;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, SERV_PORT, &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sockfd, res->ai_addr, res->ai_addrlen);
	listen(sockfd, BACKLOG);
	
	addr_size = sizeof(their_addr);

	printf("simple-webserver, all booted up.\n");

	while( (new_fd = \
		accept(sockfd, (struct sockaddr *)&their_addr, &addr_size))
		!= -1)
	{
		printf("Got one! And I am going to say Hello\n");
		char * response = "<b>How are you doing!</b>";
		send(new_fd, response, strlen(response), 0);
		printf("I just said Hi:\n%s\n", response);
		close(new_fd);
	}
}
