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

	printf("Now waiting for clients!");
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	printf("Got one! Now, I am going.");
}
