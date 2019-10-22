//	client
//	will connect to a proxy server and send it the entered url and display the response from the pserver
//
//	by Bowen Lyons
//	10/03/19

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int errorMsg(const char *type, const char *description);

int main(int argc,char **argv)
{
	
	/* check for correct command line arg count */
	if (argc != 2) {
		return errorMsg("usage","pserver <port_number>");
	}
	
	/* get port number from command line args */
	int port_number = atoi(argv[1]);
	
	/* declarations */
	int sockfd, n;
	int len = sizeof(struct sockaddr);
	char recvline[40960], url[200];
	struct sockaddr_in servaddr;
	
	/* get url from user */
	printf("url:\t");
	scanf("%s",url);
	
	/* AF_INET - IPv4 IP , Type of socket, protocol*/
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(port_number); // Server port number

	/* Convert IPv4 and IPv6 addresses from text to binary form */
	inet_pton(AF_INET,"129.120.151.94",&(servaddr.sin_addr));

	/* Connect to the server */
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	if (write(sockfd, url, strlen(url)) > 0) {
		printf("url %s sent to pserver\n", url);
	}
	while (1) {
		if (n = read(sockfd, recvline, 40959) > 0)
		{
			printf("%s\n", recvline);
			break;
		}
	}
	
}

int errorMsg(const char *type, const char *description) {
	printf("ERROR! %s: %s\n", type, description);
	return 1;
}
